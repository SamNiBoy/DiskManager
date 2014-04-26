// DiskManagerDoc.cpp : implementation of the CDiskManagerDoc class
//

#include "stdafx.h"
#include "DiskManager.h"

#include "DiskManagerDoc.h"
#include "DiskManagerView.h"
#include "LeftView.h"
#include "FileNode.h"
#include "WorkManager.h"
#include <iostream>
#include <algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CDiskManagerDoc

IMPLEMENT_DYNCREATE(CDiskManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiskManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CDiskManagerDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_DEL, OnFileDel)
	ON_COMMAND(ID_FILE_SORT_BYSZ, OnFileSortBysz)
	ON_COMMAND(ID_SORT_ACCTIME, OnSortAcctime)
	ON_COMMAND(ID_SORT_CRTTIME, OnSortCrttime)
	ON_COMMAND(ID_SORT_MODTIME, OnSortModtime)
	ON_COMMAND(ID_REFRESH_TREE, OnRefreshTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerDoc construction/destruction

CDiskManagerDoc::CDiskManagerDoc()
{
	// TODO: add one-time construction code here

	m_Path = "D:\\timesheets2";
	m_worker = NULL;
}

CDiskManagerDoc::~CDiskManagerDoc()
{
	if (m_worker)
		delete m_worker;
}

BOOL CDiskManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDiskManagerDoc serialization

void CDiskManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerDoc diagnostics

#ifdef _DEBUG
void CDiskManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiskManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerDoc commands
typedef struct param{
	CWorkManager *pWorker;
	CDiskManagerDoc *pDoc;
} PARAMFORWORKER;

PARAMFORWORKER pp;

void CDiskManagerDoc::OnFileOpen() 
{
    BROWSEINFO   bInfo; 
    ZeroMemory(&bInfo,   sizeof(bInfo)); 
    bInfo.hwndOwner   =   ::AfxGetApp()->m_pMainWnd->m_hWnd; 
    TCHAR   tchPath[255]; 
    bInfo.lpszTitle   =  _T("Please select folder: "); 
    bInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         

    LPITEMIDLIST   lpDlist; 
    lpDlist   =   SHBrowseForFolder(&bInfo);

    if(lpDlist   !=   NULL) 
	{ 
        SHGetPathFromIDList(lpDlist,  tchPath);
		m_Path = tchPath;
        //AfxMessageBox(tchPath); 
	}
	else
		return;

	// TODO: Add your command handler code here
	POSITION pos=this->GetFirstViewPosition();
	CView *pw =  this->GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
		   CFileNode::ResetCNT();
		   Files.RemoveAll();
		   CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
		   CTC.DeleteAllItems();
		   FileNode_To_hHreeItem.RemoveAll();
		   HreeItem_To_FileNode.RemoveAll();
           //ListDir(m_Path, NULL, 1);
		   AFX_THREADPROC fun = &ParseDirs;

		   if (!m_worker)
		   {
		       m_worker = new CWorkManager(::AfxGetApp()->m_pMainWnd, fun, &pp,  1);
		   }

		   pp.pDoc = this;
		   pp.pWorker = m_worker;

		   if (!m_worker->m_hWnd)
		   {
				m_worker->Create(IDD_WRK_THRD, ::AfxGetApp()->m_pMainWnd);
				
		   }

		   m_worker->ShowWindow(SW_SHOW);
		   m_worker->GetReadyForWork();

		   //

		   //pwork->m_Info = "show this?";

		   //pwork->ShowWindow(SW_SHOW);

		   //ParseDirs(&pp);

		   //pwork->ShowWindow(SW_HIDE);

		   //delete pwork;
		   //RefreshDirNodes();
		   //std::sort(arr, arr + SZ, CFileNode::SortBySize);
		   //TraceFiles();
		   //DisplayFileNodes(Files);
		}
		pw = GetNextView(pos);
	}
	::AfxGetApp()->GetMainWnd()->SetWindowText(m_Path);
}

int cnt = 0;

void CDiskManagerDoc::ListDir(CString path, CFileNode *fparent, int Level)
{
			//HTREEITEM subPar, ht;
			CString text;

			WIN32_FIND_DATA fd;
			
			HANDLE hd;
			hd = ::FindFirstFile(path+"\\*.*", &fd);
			if (hd == INVALID_HANDLE_VALUE)
				return;

			cnt ++;
			//if(cnt > 100) return;

			do
			{
				if (fd.cFileName[0] == '.') 
				{
					//::FindNextFile(hd, &fd);
					continue;
				};

				//text = fd.cFileName+text;
                //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
				//AfxMessageBox(fd.cAlternateFileName);

				CFileNode *fn = new CFileNode();
				fn->SetAttr(path, fd);
				fn->Parent = fparent;
				fn->Depth = Level;
				fn->fHandle = hd;

				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					/*subPar = CTC.InsertItem(fn->toString(), parent, TVI_LAST);
					FileNode_To_hHreeItem.SetAt(fn, subPar);
					HreeItem_To_FileNode.SetAt(subPar, fn);*/
					Files.Add(fn);
					ListDir(path+"\\"+fd.cFileName, fn, Level + 1);
				}
				else
				{
					/*ht = CTC.InsertItem(fn->toString(), parent, TVI_LAST);
					FileNode_To_hHreeItem.SetAt(fn, ht);
					HreeItem_To_FileNode.SetAt(ht, fn);*/
					Files.Add(fn);

				}

				
			} while(::FindNextFile(hd, &fd));

			//cnt = ::GetLastError();
}

UINT CDiskManagerDoc::ParseDirs(LPVOID lParam)
{
	PARAMFORWORKER* PP = (PARAMFORWORKER*) lParam;
	CWorkManager *pWorkMgr = PP->pWorker;
	CDiskManagerDoc *pDoc = PP->pDoc;
	CStatic *t = (CStatic *) pWorkMgr->GetDlgItem(IDC_STATIC_INFO);
	CProgressCtrl * p= (CProgressCtrl *) pWorkMgr->GetDlgItem(IDC_PROGRESS);
	CButton * pbtn = (CButton *) pWorkMgr->GetDlgItem(IDC_BUTTON_STST);

	CString text;
	CString path;
	CFileNode *fcurDir = NULL;
	WIN32_FIND_DATA fd;
	CObArray dirs;

	long totCnt = 0;
			
	CFileNode *Root = new CFileNode();
	Root->Path = pDoc->m_Path;
	Root->Depth = 0;
	Root->Name = "";

	dirs.Add(Root);

        while(dirs.GetSize() > 0)
		{

			fcurDir = (CFileNode*)dirs[0];

			if (pWorkMgr)
			{
			    if (::WaitForSingleObject(pWorkMgr->m_quitEvent, 0) == WAIT_OBJECT_0)
				{
					AfxMessageBox("Thread exit because of event tirggered");
					goto REND;
				}

				CString txt;
				txt.Format("Total %d folders, processing: %s\n", dirs.GetSize(), fcurDir->Path + "\\" + fcurDir->Name);
				short v = (short)((totCnt*1.0/(dirs.GetSize() + totCnt*1.0))* 100);
				//pWorkMgr->m_ProCtl.SetPos(v);

				t->SetWindowText(txt);
				
				p->SetRange(1,100);
				p->SetPos(v);
				//pWorkMgr->UpdateData(false);
				//::AfxGetApp()->m_pMainWnd->SendMessageToDescendants(WM_PAINT);
				//::SendMessage(pWorkMgr->m_hWnd, WM_PAINT, 0, 0);
				//pWorkMgr->SendMessage(WM_PAINT);
			}

			if (fcurDir->Name.GetLength() > 0)
			{
				if (fcurDir->Path.Right(1) != "\\")
				{
					path = fcurDir->Path + "\\" + fcurDir->Name;
				}
				else {
					path = fcurDir->Path + fcurDir->Name;
				}
			}
			else 
				path = fcurDir->Path;

			HANDLE hd;
			hd = ::FindFirstFile(path+"\\*.*", &fd);

			if (hd == INVALID_HANDLE_VALUE)
			{
				dirs.RemoveAt(0);
				continue;
			}

			do
			{
				if (fd.cFileName[0] == '.') 
				{
					continue;
				}

				CFileNode *fn = new CFileNode();
				fn->SetAttr(path, fd);
				fn->Parent = (fcurDir == Root) ? NULL : fcurDir;
				fn->Depth = fcurDir->Depth + 1;
				fn->fHandle = hd;

				totCnt++;

				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					pDoc->Files.Add(fn);
					//ListDir(path+"\\"+fd.cFileName, fn, Level + 1);
					dirs.Add(fn);
				}
				else
				{
					pDoc->Files.Add(fn);
				}
			} while(::FindNextFile(hd, &fd));

			dirs.RemoveAt(0);
		}

		delete Root;

REND:
		t->SetWindowText("Refreshing directories information...");
		pDoc->RefreshDirNodes();
		t->SetWindowText("Creating file tree...");
		pDoc->DisplayFileNodes(pDoc->Files);

	if (pWorkMgr)
	{
		t->SetWindowText("Completed!");
		p->SetRange(1,100);
		p->SetPos(100);
		pWorkMgr->ShowWindow(SW_HIDE);
		pWorkMgr->m_Thread = NULL;
	}
    return 0;
}
void CDiskManagerDoc::DisplayFileNodes(CObArray &files)
{

	HTREEITEM lstParent = NULL, ht;
	CFileNode *fn, *fpar = NULL;
	CObArray Stack;
	CTreeCtrl *CTC;

	FileNode_To_hHreeItem.RemoveAll();
	HreeItem_To_FileNode.RemoveAll();

	POSITION pos=this->GetFirstViewPosition();
	CView *pw =  this->GetNextView(pos);

	while(pw)
	{
	    if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
		   CTC = &((CLeftView*)pw)->GetTreeCtrl();
		   break;
		}
		pw = GetNextView(pos);
	}

	CTC->ShowWindow(SW_HIDE);
	CTC->DeleteAllItems();

	for (int i=0;i<files.GetSize();i++)
	{
		fn = (CFileNode*) files[i];

		ht = NULL;

		FileNode_To_hHreeItem.Lookup(fn, (void*&)ht);

		if (ht)
			continue;

		lstParent = NULL;
		if (fn->Parent)
		{
			FileNode_To_hHreeItem.Lookup(fn->Parent, (void*&)ht);

			if (ht)
				lstParent = ht;
			else
			{
				ht = NULL;
				Stack.Add(fn->Parent);
				CFileNode *PPar = fn->Parent->Parent;
				while (PPar)
				{
					Stack.Add(PPar);
					PPar = PPar->Parent;
				}
				
				while(Stack.GetSize() > 0)
				{
					PPar = (CFileNode*)Stack[Stack.GetSize() - 1];

					ht = NULL;

					FileNode_To_hHreeItem.Lookup(PPar, (void*&)ht);

					if (ht)
					{
						Stack.RemoveAt(Stack.GetSize() - 1);
						continue;
					}
					else
					{

						if (PPar->Parent)
						{
						    FileNode_To_hHreeItem.Lookup(PPar->Parent, (void*&)ht);
							if (ht)
								lstParent = ht;
							else 
							{
								AfxMessageBox("Exception!");
							}
						}
						ht = CTC->InsertItem(PPar->toString(), lstParent? lstParent : TVI_ROOT, TVI_LAST);
						FileNode_To_hHreeItem.SetAt(PPar, ht);
		                HreeItem_To_FileNode.SetAt(ht, PPar);
						Stack.RemoveAt(Stack.GetSize() - 1);
					}
				}
				FileNode_To_hHreeItem.Lookup(fn->Parent, (void*&)lstParent);
			}
		}

		ht = CTC->InsertItem(fn->toString(), lstParent? lstParent : TVI_ROOT, TVI_LAST);
		//ht = CTC.InsertItem(fn->toString(), TVI_ROOT, TVI_LAST);


		FileNode_To_hHreeItem.SetAt(fn, ht);
		HreeItem_To_FileNode.SetAt(ht, fn);
	}
	CTC->ShowWindow(SW_SHOW);
}

void CDiskManagerDoc::RefreshDirNodes()
{
	int idx = 0;
    for(int i=Files.GetSize() - 1;i>=0; i--)
	{
		CFileNode *fn = (CFileNode*)Files[i];

		if (fn->IsDir)
		{
			fn->Size.LowPart = 0;
			fn->Size.HighPart = 0;
			idx = i+1;
			while (idx < Files.GetSize())
			{
			    CFileNode *son = (CFileNode*)Files[idx];

				if (son->Parent != fn)
				{
				    if (son->Depth > fn->Depth + 1)
					{
					    break;
					}
					idx ++;
					continue;
				}

				//fn->Size.QuadPart += son->Size.QuadPart;
	            fn->Size.LowPart += son->Size.LowPart;
                fn->Size.HighPart += son->Size.HighPart;
				idx ++;
			}
		}
	}
}

void CDiskManagerDoc::TraceFiles()
{
    for(int i=0;i<Files.GetSize();i++)
	{
		CFileNode *fn = ((CFileNode*)Files[i]);
		TRACE("File[%s],ID[%ld],SZ[%ld | %ld]\n", fn->Name, fn->ID, fn->Size.HighPart, fn->Size.LowPart);
	}
}


void CDiskManagerDoc::OnFileDel() 
{
	// TODO: Add your command handler code here
	POSITION pos=this->GetFirstViewPosition();
	CView *pw =  this->GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
		   CFileNode::ResetCNT();
		   CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
		   HTREEITEM sel;
		   sel = CTC.GetSelectedItem();
		   if (sel != NULL)
		   {
		       CFileNode *fn = NULL;
		       HreeItem_To_FileNode.Lookup(sel, (void*&)fn);
			   if (fn)
			   {
				   if (AfxMessageBox("Deleting file: " + fn->GetFullFileName() + "?", MB_YESNO|MB_ICONINFORMATION) == IDYES)
				   {
					   if (fn->IsDir)
					   {
						   if (DeleteDirectory(fn))
						   {
					          CTC.DeleteItem(sel);
					          RemoveFileNode(fn);
						   }
						   else
						   {
							   //int errcod = ::GetLastError();
							   LPVOID lpMsgBuf;
							   ::FormatMessage(
                                            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                            FORMAT_MESSAGE_FROM_SYSTEM |
                                            FORMAT_MESSAGE_IGNORE_INSERTS,
                                            NULL,
                                            GetLastError(),
                                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                            (LPTSTR) &lpMsgBuf,
                                            0,
										    NULL);
							   AfxMessageBox((LPCTSTR)lpMsgBuf, MB_OK | MB_ICONINFORMATION );
							   LocalFree( lpMsgBuf );
							   //CString s;
							   //s.Format("Deleting directory failed with error: %d", errcod);
							   //AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
						   }
					   }
					   else
					   {
					       if (::DeleteFile(fn->GetFullFileName()))
						   {
					          CTC.DeleteItem(sel);
					          RemoveFileNode(fn);
						   }
						   else
						   {
							   /*int errcod = ::GetLastError();
							   CString s;
							   s.Format("Deleting file failed with error: %d", errcod);
							   AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);*/
							   LPVOID lpMsgBuf;
							   ::FormatMessage(
                                            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                            FORMAT_MESSAGE_FROM_SYSTEM |
                                            FORMAT_MESSAGE_IGNORE_INSERTS,
                                            NULL,
                                            GetLastError(),
                                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                            (LPTSTR) &lpMsgBuf,
                                            0,
										    NULL);
							   AfxMessageBox((LPCTSTR)lpMsgBuf, MB_OK | MB_ICONINFORMATION );
							   LocalFree( lpMsgBuf );
						   }
					   }
				   }
			   }
		   }
		   //DisplayFileNodes(CTC, Files);
		}
		pw = GetNextView(pos);
	}	
}

void CDiskManagerDoc::RemoveFileNode(CFileNode *fn)
{
	int beg;
	HTREEITEM ht = NULL;
	/*while(idx < Files.GetSize())
	{
		CFileNode *fcur = (CFileNode*) Files[idx];
		if (fcur->Depth == fn->Depth)
			break;
	}
	end = idx - 1;

	CFileNode *fdel = NULL;
	HTREEITEM ht = NULL;
	for (idx = beg; idx <= end; idx++)
	{
		ht = NULL;
        fdel = (CFileNode*) Files[idx];
		FileNode_To_hHreeItem.Lookup(fdel, (void *&) ht);
		HreeItem_To_FileNode.RemoveKey(ht);
		FileNode_To_hHreeItem.RemoveKey(fdel);
		delete fdel;
	}

	idx = end + 1;
	while (idx < Files.GetSize())
	{
		Files[beg] = Files[idx];
		beg++;
		idx++;
	}

	while (beg < Files.GetSize())
	{
		Files.RemoveAt(beg++);
	}*/
	CObArray fls;
	fls.Append(Files);
	Files.RemoveAll();

	CObArray dirAry;
	dirAry.Add(fn);

	for (beg = 0; beg < fls.GetSize(); beg++)
	{
		CFileNode *fcur = (CFileNode*) fls[beg];

		for (int j = 0; j< dirAry.GetSize(); j++)
		{
			CFileNode *fpar = (CFileNode*) dirAry[j];
			if (fcur->Parent == fpar || fcur == fpar)
			{
			    if (fcur->IsDir)
				    dirAry.Add(fcur);

				delete fcur;

				FileNode_To_hHreeItem.Lookup(fcur, (void *&) ht);
		        HreeItem_To_FileNode.RemoveKey(ht);
		        FileNode_To_hHreeItem.RemoveKey(fcur);

				break;
			}
			else
				Files.Add(fcur);
		}
	}
}

int CDiskManagerDoc::DeleteDirectory(CFileNode *fdir)
{
	int beg;
	HTREEITEM ht = NULL;

	CObArray dirAry;
	dirAry.Add(fdir);

	for (beg = 0; beg < Files.GetSize(); beg++)
	{
		CFileNode *fcur = (CFileNode*) Files[beg];

		for (int j = 0; j< dirAry.GetSize(); j++)
		{
			CFileNode *fpar = (CFileNode*) dirAry[j];
			if (fcur->Parent == fpar || fcur == fpar)
			{
			    if (fcur->IsDir)
				{
					if (fcur != fdir)
				        dirAry.Add(fcur);
				}
				else
				{
					if (!::DeleteFile(fcur->GetFullFileName()))
					    return 0;
					::FindClose(fcur->fHandle);
				}

				break;
			}
		}
	}

	/* Remove empty folders, make sure remove absolute empty folders first */
	while(dirAry.GetSize() > 0)
	{
		for (beg = 0; beg < dirAry.GetSize(); beg++)
		{
			int delflg = 1;
		    CFileNode *fEmptydir = (CFileNode*) dirAry[beg];
	        for (int i = 0; i < dirAry.GetSize(); i++)
			{
				if (i == beg)
					continue;

			    CFileNode* fsub = (CFileNode*) dirAry[i];
			    if (fEmptydir ==  fsub->Parent)
				{
					delflg = 0;
				    break;
				}
			}

			if (delflg)
			{
				if (!::RemoveDirectory(fEmptydir->GetFullFileName()))
			        return 0;
		        ::FindClose(fEmptydir->fHandle);
				dirAry.RemoveAt(beg);
				break;
			}
		}
	}

	return 1;
}

void CDiskManagerDoc::OnFileSortBysz() 
{
	// TODO: Add your command handler code here
	CObArray fls;

	fls.Append(Files);

	::qsort((void*) fls.GetData(), fls.GetSize(), sizeof(CFileNode*), CFileNode::SortBySize);

	POSITION pos = GetFirstViewPosition();
	CView *pw =  GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
			CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
			CFileNode::SHOWMOD = SHOWSIZE;
			DisplayFileNodes(fls);
		}
		pw = GetNextView(pos);
	}
	
}


void CDiskManagerDoc::OnSortAcctime() 
{
	// TODO: Add your command handler code here
	CObArray fls;

	fls.Append(Files);

	::qsort((void*) fls.GetData(), fls.GetSize(), sizeof(CFileNode*), CFileNode::SortByAccTime);

	POSITION pos = GetFirstViewPosition();
	CView *pw =  GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
			CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
			CFileNode::SHOWMOD = SHOWACCTIME;
			DisplayFileNodes(fls);
		}
		pw = GetNextView(pos);
	}	
}

void CDiskManagerDoc::OnSortCrttime() 
{
	// TODO: Add your command handler code here
	CObArray fls;

	fls.Append(Files);

	::qsort((void*) fls.GetData(), fls.GetSize(), sizeof(CFileNode*), CFileNode::SortByCrtTime);

	POSITION pos = GetFirstViewPosition();
	CView *pw =  GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
			CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
			CFileNode::SHOWMOD = SHOWCRTTIME;
			DisplayFileNodes(fls);
		}
		pw = GetNextView(pos);
	}	
}

void CDiskManagerDoc::OnSortModtime() 
{
	// TODO: Add your command handler code here
	CObArray fls;

	fls.Append(Files);

	::qsort((void*) fls.GetData(), fls.GetSize(), sizeof(CFileNode*), CFileNode::SortByModTime);

	POSITION pos = GetFirstViewPosition();
	CView *pw =  GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
			CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
			CFileNode::SHOWMOD = SHOWMODTIME;
			DisplayFileNodes(fls);
		}
		pw = GetNextView(pos);
	}
}

void CDiskManagerDoc::OnRefreshTree() 
{
	// TODO: Add your command handler code here

	POSITION pos = GetFirstViewPosition();
	CView *pw =  GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{

		}
		else if (pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{
			CTreeCtrl &CTC = ((CLeftView*)pw)->GetTreeCtrl();
			DisplayFileNodes(Files);
		}
		pw = GetNextView(pos);
	}	
}

void CDiskManagerDoc::OpenFolder(HTREEITEM hItem)
{

	CFileNode *fSel = NULL;
	HreeItem_To_FileNode.Lookup(hItem, (void*&) fSel);

	if (!fSel)
		return;

	fSel->OpenFolder();
}
