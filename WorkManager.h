#if !defined(AFX_WORKMANAGER_H__9A04BCFE_5BC2_4569_B3BB_188473A27399__INCLUDED_)
#define AFX_WORKMANAGER_H__9A04BCFE_5BC2_4569_B3BB_188473A27399__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkManager dialog

//typedef UINT(*WORKFUN)(LPVOID);

class CWorkManager : public CDialog
{
// Construction
public:
	void DoWork();
	void GetReadyForWork();
	AFX_THREADPROC m_Worker;
	bool m_Start;
	CWinThread *m_Thread;
    HANDLE m_quitEvent;
	LPVOID m_lpPara;
	CWorkManager(CWnd* pParent , AFX_THREADPROC pProFun,LPVOID parameter,  bool suspend);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkManager)
	enum { IDD = IDD_WRK_THRD };
	CButton	m_BtnQuit;
	CButton	m_BtnSS;
	CProgressCtrl	m_ProCtl;
	CString	m_Info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkManager)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkManager)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStst();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnButtonQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKMANAGER_H__9A04BCFE_5BC2_4569_B3BB_188473A27399__INCLUDED_)
