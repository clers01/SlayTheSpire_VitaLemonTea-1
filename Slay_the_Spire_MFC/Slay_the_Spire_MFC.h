
// Slay_the_Spire_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSlay_the_Spire_MFCApp:
// See Slay_the_Spire_MFC.cpp for the implementation of this class
//

class CSlay_the_Spire_MFCApp : public CWinApp
{
public:
	CSlay_the_Spire_MFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSlay_the_Spire_MFCApp theApp;