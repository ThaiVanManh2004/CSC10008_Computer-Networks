
#include "pch.h"
#include "ClientSocket.h"
#include "Client.h"
#define RECV_BUFFER_SIZE 4096
#define IDC_IMAGE 1013
#include "afxdialogex.h"
#include <afxwin.h>
#include <afxcmn.h>

#include <Windows.h>
#include <string>
#include <atlimage.h>  // for CImage
#include <gdiplus.h>
#include "MainFrm.h"

void CClientSocket::OnReceive(int nErrorCode)
{
	// local variables used in file transfer (declared here to avoid
	// "goto skips definition"-style compiler errors)

	BOOL bRet = TRUE; // return value
	// used to monitor the progress of a receive operation
	int dataLength, cbBytesRet, cbLeftToReceive;
	// pointer to buffer for receiving data
	// (memory is allocated after obtaining file size)
	BYTE* recdData = NULL;

	CFile destFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;

	// open/create target file that receives the transferred data

	if (!(bFileIsOpen = destFile.Open(L"screenshot1.bmp", CFile::modeCreate |
		CFile::modeWrite | CFile::typeBinary, &fe)))
	{
		TCHAR strCause[256];
		fe.GetErrorMessage(strCause, 255);
		TRACE("GetFileFromRemoteSender encountered an error while opening the local file\n"
			"\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError);

		/* you should handle the error here */

		bRet = FALSE;
		goto PreReturnCleanup;
	}

	// get the file's size first
	cbLeftToReceive = sizeof(dataLength);

	do
	{
		BYTE* bp = (BYTE*)(&dataLength) + sizeof(dataLength) - cbLeftToReceive;
		cbBytesRet = ((CClientApp*)AfxGetApp())->m_ClientSocket.Receive(bp, cbLeftToReceive);

		// test for errors and get out if they occurred
		if (cbBytesRet == SOCKET_ERROR || cbBytesRet == 0)
		{
			int iErr = ::GetLastError();
			TRACE("GetFileFromRemoteSite returned a socket error while getting file length\n"
				"\tNumber of Bytes received (zero means connection was closed) = %d\n"
				"\tGetLastError = %d\n", cbBytesRet, iErr);

			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}

		// good data was retrieved, so accumulate
		// it with already-received data
		cbLeftToReceive -= cbBytesRet;

	} while (cbLeftToReceive > 0);

	dataLength = ntohl(dataLength);

	// now get the file in RECV_BUFFER_SIZE chunks at a time

	recdData = new byte[RECV_BUFFER_SIZE];
	cbLeftToReceive = dataLength;

	do
	{
		int iiGet, iiRecd;

		iiGet = (cbLeftToReceive < RECV_BUFFER_SIZE) ?
			cbLeftToReceive : RECV_BUFFER_SIZE;
		iiRecd = ((CClientApp*)AfxGetApp())->m_ClientSocket.Receive(recdData, iiGet);

		// test for errors and get out if they occurred
		if (iiRecd == SOCKET_ERROR || iiRecd == 0)
		{
			int iErr = ::GetLastError();
			TRACE("GetFileFromRemoteSite returned a socket error while getting chunked file data\n"
				"\tNumber of Bytes received (zero means connection was closed) = %d\n"
				"\tGetLastError = %d\n", iiRecd, iErr);

			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}

		// good data was retrieved, so accumulate
		// it with already-received data

		destFile.Write(recdData, iiRecd); // Write it
		cbLeftToReceive -= iiRecd;

	} while (cbLeftToReceive > 0);
	
PreReturnCleanup: // labelled "goto" destination

	// free allocated memory
	// if we got here from a goto that skipped allocation,
	// delete of NULL pointer
	// is permissible under C++ standard and is harmless
	delete[] recdData;

	if (bFileIsOpen) {
		destFile.Close();
		bFileIsOpen = false;
	}
	if (!bFileIsOpen) {
		((CMainFrame*)AfxGetMainWnd())->OnDisplayImage();
	}
	((CClientApp*)AfxGetApp())->m_ClientSocket.Send("TVM", 3);
	// only close file if it's open (open might have failed above)


	
	CSocket::OnReceive(nErrorCode);
}
