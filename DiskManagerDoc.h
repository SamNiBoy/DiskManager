// DiskManagerDoc.h : interface of the CDiskManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include"FileNode.h"
#include"WorkManager.h"
#if !defined(AFX_DISKMANAGERDOC_H__30641566_FDE7_4400_9A0B_49344AEFDEF8__INCLUDED_)
#define AFX_DISKMANAGERDOC_H__30641566_FDE7_4400_9A0B_49344AEFDEF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiskManagerDoc : public CDocument
{
protected: // create from serialization only
	CDiskManagerDoc();
	DECLARE_DYNCREATE(CDiskManagerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
    static UINT CDiskManagerDoc::ParseDirs(LPVOID lParam);
	void OpenFolder(HTREEITEM hItem);
	int DeleteDirectory(CFileNode*fdir);
	void RemoveFileNode(CFileNode *fn);
	void TraceFiles();
	void RefreshDirNodes();
	void DisplayFileNodes(CObArray & files);
	void ListDir(CString path, CFileNode *fparent, int Level);
	CString m_Path;
	CMapPtrToPtr FileNode_To_hHreeItem;
    CMapPtrToPtr HreeItem_To_FileNode;
	CObArray Files;
	CWorkManager *m_worker;
	virtual ~CDiskManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiskManagerDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileDel();
	afx_msg void OnFileSortBysz();
	afx_msg void OnSortAcctime();
	afx_msg void OnSortCrttime();
	afx_msg void OnSortModtime();
	afx_msg void OnRefreshTree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISKMANAGERDOC_H__30641566_FDE7_4400_9A0B_49344AEFDEF8__INCLUDED_)
