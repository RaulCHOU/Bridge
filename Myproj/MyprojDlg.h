// MyprojDlg.h : header file
//

#if !defined(AFX_MYPROJDLG_H__2C4F0410_2BC5_455F_82AF_0B177B27D0A9__INCLUDED_)
#define AFX_MYPROJDLG_H__2C4F0410_2BC5_455F_82AF_0B177B27D0A9__INCLUDED_

#include "BasicExcel.h"	// Added by ClassView
#include "PCA_Demension.h"
using namespace YExcel;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyprojDlg dialog


class CMyprojDlg : public CDialog
{
// Construction
public:
	CMyprojDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyprojDlg)
	enum { IDD = IDD_MYPROJ_DIALOG };
	CListCtrl	m_List2;
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyprojDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
public:
	void predict(Tree tree,vector<vector<double> > rules,int dex);

//	void Init_size(size_t x,size_t y);
//	vector<vector<double> > data;

	//	vector<vector<double> > & Features;
//	vector<vector<double> > & Final_Data;
	// Generated message map functions
	//{{AFX_MSG(CMyprojDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	virtual void OnCancel();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int jacbi_ord_Dlg[100];
	int attr_num;
	BasicExcelWorksheet* sheet1;
	BasicExcelWorksheet* sheet2;
	BasicExcel e;
	BasicExcel e2;
	int maxCols;
	int maxRows;
	int nvar;
	double data_label[1000];
	double test_label[1000];
	Tree tree;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROJDLG_H__2C4F0410_2BC5_455F_82AF_0B177B27D0A9__INCLUDED_)
