// WorkManager.cpp : implementation file
//

#include "stdafx.h"
#include "DiskManager.h"
#include "WorkManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkManager dialog



CWorkManager::CWorkManager(CWnd* pParent , AFX_THREADPROC pProFun, LPVOID parameter, bool suspend)
	: CDialog(CWorkManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkManager)
	m_Info = _T("");
	//}}AFX_DATA_INIT
	m_Thread = NULL;
	m_Start = !suspend;
	m_Worker = pProFun;
	m_lpPara = parameter;
}


void CWorkManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkManager)
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_BtnQuit);
	DDX_Control(pDX, IDC_BUTTON_STST, m_BtnSS);
	DDX_Control(pDX, IDC_PROGRESS, m_ProCtl);
	DDX_Text(pDX, IDC_STATIC_INFO, m_Info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkManager, CDialog)
	//{{AFX_MSG_MAP(CWorkManager)
	ON_BN_CLICKED(IDC_BUTTON_STST, OnButtonStst)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkManager message handlers

BOOL CWorkManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CFont   m_Font; 
    m_Font.CreateFont(-11,0,0,0,100,FALSE,FALSE,0, 
                    ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,FF_SWISS, "Arial ");
	m_BtnSS.SetFont(&m_Font);
	m_BtnQuit.SetFont(&m_Font);
	CStatic *ptxt = (CStatic*) GetDlgItem(IDC_STATIC_INFO);
	ptxt->SetFont(&m_Font);

	m_Font.Detach();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorkManager::DoWork()
{
	if (!m_Thread)
	{
	    m_Thread = AfxBeginThread(m_Worker,
		                      m_lpPara,
							  THREAD_PRIORITY_NORMAL,
							  0,
							  (!m_Start) ? CREATE_SUSPENDED : 0);

		m_quitEvent = ::CreateEvent(NULL, true, false, NULL);
		//
	}

	if (m_Start)
	{
		m_BtnSS.SetWindowText("Start");
	    m_Start = false;
	    //::SuspendThread(m_Thread);
		m_Thread->SuspendThread();
	}
	else
	{
		m_BtnSS.SetWindowText("Stop");
	    m_Start = true;
	    //::ResumeThread(m_Thread);
		m_Thread->ResumeThread();
	}
}


void CWorkManager::OnButtonStst() 
{
	// TODO: Add your control notification handler code here

    DoWork();

}

void CWorkManager::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//m_Thread->ExitInstance();
	//AfxTermThread();
	
	m_Thread->PostThreadMessage(WM_QUIT,0,0);
	CDialog::OnClose();
	
	//delete m_Thread;
	//delete this;
}

void CWorkManager::OnDestroy() 
{
	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CWorkManager::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//
	return CDialog::DestroyWindow();
}

void CWorkManager::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	SetEvent(m_quitEvent);
	::CloseHandle(m_quitEvent);
	//ShowWindow(SW_HIDE);
}

void CWorkManager::GetReadyForWork()
{
	m_Start = 0;
	m_BtnSS.SetWindowText("Start");
	m_Thread = NULL;
    m_Info = "Ready to Go:";
	m_ProCtl.SetPos(0);
	UpdateData(false);
}

BOOL CWorkManager::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}
