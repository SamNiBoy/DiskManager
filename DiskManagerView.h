// DiskManagerView.h : interface of the CDiskManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISKMANAGERVIEW_H__6B63B6A6_2BB1_4F15_8E4C_D47444C69D47__INCLUDED_)
#define AFX_DISKMANAGERVIEW_H__6B63B6A6_2BB1_4F15_8E4C_D47444C69D47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiskManagerView : public CListView
{
protected: // create from serialization only
	CDiskManagerView();
	DECLARE_DYNCREATE(CDiskManagerView)

// Attributes
public:
	CDiskManagerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiskManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiskManagerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DiskManagerView.cpp
inline CDiskManagerDoc* CDiskManagerView::GetDocument()
   { return (CDiskManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISKMANAGERVIEW_H__6B63B6A6_2BB1_4F15_8E4C_D47444C69D47__INCLUDED_)
