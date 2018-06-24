// Myproj.h : main header file for the MYPROJ application
//

#if !defined(AFX_MYPROJ_H__8FEF9F71_C1CB_45B9_B083_7589DF80FFC6__INCLUDED_)
#define AFX_MYPROJ_H__8FEF9F71_C1CB_45B9_B083_7589DF80FFC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyprojApp:
// See Myproj.cpp for the implementation of this class
//

class CMyprojApp : public CWinApp
{
public:
	BOOL ExitInstance();

	CMyprojApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyprojApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyprojApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROJ_H__8FEF9F71_C1CB_45B9_B083_7589DF80FFC6__INCLUDED_)
