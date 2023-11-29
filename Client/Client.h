
// Client.h : main header file for the Client application
//
#pragma once

#include "resource.h"       // main symbols
//
#include "ClientSocket.h"
//


// CClientApp:
// See Client.cpp for the implementation of this class
//

class CClientApp : public CWinAppEx
{
// Overrides
public:
	virtual BOOL InitInstance();

//
	CClientSocket m_ClientSocket;
//
};