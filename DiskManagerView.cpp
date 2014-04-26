// DiskManagerView.cpp : implementation of the CDiskManagerView class
//

#include "stdafx.h"
#include "DiskManager.h"

#include "DiskManagerDoc.h"
#include "DiskManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerView

IMPLEMENT_DYNCREATE(CDiskManagerView, CListView)

BEGIN_MESSAGE_MAP(CDiskManagerView, CListView)
	//{{AFX_MSG_MAP(CDiskManagerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerView construction/destruction

CDiskManagerView::CDiskManagerView()
{
	// TODO: add construction code here

}

CDiskManagerView::~CDiskManagerView()
{
}

BOOL CDiskManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerView drawing

void CDiskManagerView::OnDraw(CDC* pDC)
{
	CDiskManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CDiskManagerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
    CListCtrl &LC = GetListCtrl();
	LC.InsertColumn(0, "Name");
	//LC.SetColumnWidth(0, 2500);
	LC.InsertColumn(1, "Size");
	//LC.SetColumnWidth(1, 2250);

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerView diagnostics

#ifdef _DEBUG
void CDiskManagerView::AssertValid() const
{
	CListView::AssertValid();
}

void CDiskManagerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDiskManagerDoc* CDiskManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiskManagerDoc)));
	return (CDiskManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiskManagerView message handlers
void CDiskManagerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
