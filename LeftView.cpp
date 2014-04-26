// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "DiskManager.h"

#include "DiskManagerDoc.h"
#include "DiskManagerView.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(IDM_DEL_FILE, OnDelFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= TVS_HASLINES |TVS_LINESATROOT |TVS_SHOWSELALWAYS |TVS_HASBUTTONS ;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CDiskManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//HTREEITEM hTreeItem, hParTreeItem;

	 CTreeCtrl &CTC = GetTreeCtrl();

	 /*hTreeItem=CTC.InsertItem("TEST",
						                      1,
											  1,
						                      TVI_ROOT,
											  TVI_LAST);
											  */
	 CTC.InsertItem("TEST2");
	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CTreeCtrl &CTC = GetTreeCtrl();
	//CTC.InsertItem("TEST");
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDiskManagerDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiskManagerDoc)));
	return (CDiskManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
		 CTreeCtrl &CTC = GetTreeCtrl();

		 AfxMessageBox("No ok!", MB_OK);
	 /*hTreeItem=CTC.InsertItem("TEST",
						                      1,
											  1,
						                      TVI_ROOT,
											  TVI_LAST);
											  */
	 
	//CTreeView::OnPrint(pDC, pInfo);
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	//AfxMessageBox("No ok!", MB_OK);
	
}

void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CDiskManagerDoc* pDoc = GetDocument();
	CTreeCtrl &CTC = this->GetTreeCtrl();

	HTREEITEM hTreeItem;

	hTreeItem = CTC.GetSelectedItem();

	pDoc->OpenFolder(hTreeItem);

	*pResult = 0;
}

void CLeftView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hTreeItem;
	//hTreeItem = pNMTreeView->itemNew.hItem;

	CTreeCtrl &CTC = this->GetTreeCtrl();
	CPoint point;  
    TVHITTESTINFO HitTestInfo;  
    GetCursorPos(&point);
    CTC.ScreenToClient(&point);  
    HitTestInfo.pt = point;
    //hTreeItem = CTC.HitTest(&HitTestInfo);
	hTreeItem = CTC.GetSelectedItem();

	CDiskManagerDoc *pDoc = GetDocument();
	int ID = 0;
	CFileNode *fSel = NULL;

	if (hTreeItem)
	{
		pDoc->HreeItem_To_FileNode.Lookup(hTreeItem, (void*&)fSel);
		if (fSel)
		{
		}
	}

	POSITION pos=pDoc->GetFirstViewPosition();
	CView *pw =  pDoc->GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CDiskManagerView)))
		{
			CDiskManagerView *pLstView = (CDiskManagerView*) pw;
			CListCtrl &LCTL = pLstView->GetListCtrl();
			/*
			 * 	BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
		     *  int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
		     */
			LCTL.SetItem(ID, 0, 0, fSel->GetFullFileName(), 0, 0, 0, NULL);
			ID++;

			break;
		}
		pw =  pDoc->GetNextView(pos);
	}

	
	*pResult = 0;
}

void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    CPoint point;  
	GetCursorPos(&point);
	CMenu mn, *pMenu;
	mn.LoadMenu(IDR_MENU_DEL);
	pMenu=&mn;
    pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x,point.y,this);
    
	*pResult = 0;
}

void CLeftView::OnDelFile() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("deleteing file");
}
