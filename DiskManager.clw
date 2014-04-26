; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DiskManager.h"
LastPage=0

ClassCount=7
Class1=CDiskManagerApp
Class2=CDiskManagerDoc
Class3=CDiskManagerView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_MENU_DEL
Class5=CLeftView
Class6=CAboutDlg
Resource2=IDD_ABOUTBOX
Resource3=IDD_ABOUTBOX (Chinese (P.R.C.))
Resource4=IDR_MAINFRAME (Chinese (P.R.C.))
Class7=CWorkManager
Resource5=IDD_WRK_THRD
Resource6=IDR_MAINFRAME
Resource7=IDD_WRK_THRD (English (U.S.))

[CLS:CDiskManagerApp]
Type=0
HeaderFile=DiskManager.h
ImplementationFile=DiskManager.cpp
Filter=N

[CLS:CDiskManagerDoc]
Type=0
HeaderFile=DiskManagerDoc.h
ImplementationFile=DiskManagerDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDiskManagerDoc

[CLS:CDiskManagerView]
Type=0
HeaderFile=DiskManagerView.h
ImplementationFile=DiskManagerView.cpp
Filter=C
LastObject=CDiskManagerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
LastObject=IDM_DEL_FILE
BaseClass=CTreeView
VirtualFilter=VWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DiskManager.cpp
ImplementationFile=DiskManager.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=CDiskManagerDoc
Command1=ID_FILE_OPEN
Command2=ID_FILE_DEL
Command3=ID_FILE_SORT_BYSZ
Command4=ID_SORT_CRTTIME
Command5=ID_SORT_ACCTIME
Command6=ID_SORT_MODTIME
Command7=ID_REFRESH_TREE
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_HELP
Command4=ID_APP_ABOUT
CommandCount=4

[TB:IDR_MAINFRAME (Chinese (P.R.C.))]
Type=1
Class=CDiskManagerDoc
Command1=ID_FILE_OPEN
Command2=ID_FILE_DEL
Command3=ID_FILE_SORT_BYSZ
Command4=ID_SORT_CRTTIME
Command5=ID_SORT_ACCTIME
Command6=ID_SORT_MODTIME
Command7=ID_REFRESH_TREE
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (Chinese (P.R.C.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_HELP
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME (Chinese (P.R.C.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (Chinese (P.R.C.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WRK_THRD]
Type=1
Class=CWorkManager
ControlCount=4
Control1=IDC_STATIC_INFO,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDC_BUTTON_STST,button,1342242816
Control4=IDC_BUTTON_QUIT,button,1342242816

[CLS:CWorkManager]
Type=0
HeaderFile=WorkManager.h
ImplementationFile=WorkManager.cpp
BaseClass=CDialog
Filter=D
LastObject=CWorkManager
VirtualFilter=dWC

[DLG:IDD_WRK_THRD (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC_INFO,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDC_BUTTON_STST,button,1342242816
Control4=IDC_BUTTON_QUIT,button,1342242816

[MNU:IDR_MENU_DEL]
Type=1
Class=CLeftView
Command1=IDM_DEL_FILE
CommandCount=1

