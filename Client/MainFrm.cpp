
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "Client.h"

#include "MainFrm.h"

// CMainFrame
#include "afxwin.h"



IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	//
	ON_BN_CLICKED(IDC_BUTTON, OnButtonClicked)
	//
	//ON_COMMAND(ID_DISPLAY_IMAGE, OnDisplayImage) 
	//
END_MESSAGE_MAP()

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//
	cButton.Create(_T(""), BS_DEFPUSHBUTTON, CRect(0, 0, 0, 0), this, IDC_BUTTON);
	cButton.ShowWindow(SW_SHOWMAXIMIZED);
	return 0;
}
void CMainFrame::OnDisplayImage()
{
	(& cButton)->ShowWindow(SW_HIDE);
	CRect rect;
	GetClientRect(&rect);
	//CRect rect(0, 0, 1000, 2000);
	if (create == false) {
		m_pictureCtrl->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, rect, this);
		create = true;
	}


	//ScreenToClient(&rect);
	CImage m_image;
	m_image.Load(_T("screenshot1.bmp"));
	// Scale the image to fit the picture control box
	CImage scaledImage;
	double scaleX = (double)rect.Width() / (double)m_image.GetWidth();
	double scaleY = (double)rect.Height() / (double)m_image.GetHeight();
	double scale = min(scaleX, scaleY);
	int newWidth = (int)(scale * m_image.GetWidth());
	int newHeight = (int)(scale * m_image.GetHeight());
	scaledImage.Create(newWidth, newHeight, m_image.GetBPP());

	// Draw the original image onto the scaled image using GDI functions
	HDC hDC = scaledImage.GetDC();
	HDC hDCOrig = m_image.GetDC();
	SetStretchBltMode(hDC, HALFTONE);
	StretchBlt(hDC, 0, 0, newWidth, newHeight, hDCOrig, 0, 0, m_image.GetWidth(), m_image.GetHeight(), SRCCOPY);
	scaledImage.ReleaseDC();
	m_image.ReleaseDC();

	(m_pictureCtrl)->SetBitmap(scaledImage.Detach());
}
//
void CMainFrame::OnButtonClicked() {
	if (((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket == INVALID_SOCKET)
		((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Create(1, SOCK_DGRAM);
	else {
		((CClientApp*)AfxGetApp())->m_ClientSocket.Create();
		((CClientApp*)AfxGetApp())->m_ClientSocket.Connect(((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketAddress, ((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.rSocketPort);
		((CClientApp*)AfxGetApp())->m_ClientSocket.Send("TVM", 3);
		((CClientApp*)AfxGetApp())->m_ClientSocket.m_ReceivingSocket.Close();
	}
}
//