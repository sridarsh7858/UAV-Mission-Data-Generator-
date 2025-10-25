
// XMLGen.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXMLGenApp:
// See XMLGen.cpp for the implementation of this class
//

class CXMLGenApp : public CWinApp
{
public:
	CXMLGenApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CXMLGenApp theApp;
