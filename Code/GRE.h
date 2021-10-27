// GRE.h : main header file for the GRE application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// GREApp:
// See GRE.cpp for the implementation of this class
//

class GREApp : public CWinApp
{
public:
	GREApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern GREApp theApp;
