
// Server.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "Server.h"
#include "MainFrm.h"


// The one and only CServerApp object

CServerApp theApp;


// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME);





	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	//
	m_pMainWnd->SetMenu(NULL);
	//
	return TRUE;
}
