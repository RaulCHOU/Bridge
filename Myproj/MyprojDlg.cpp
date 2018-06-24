// MyprojDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Myproj.h"
#include "MyprojDlg.h"

#include "BasicExcel.h"
#include "PCA_Demension.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace YExcel;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyprojDlg dialog

CMyprojDlg::CMyprojDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyprojDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyprojDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyprojDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyprojDlg)
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyprojDlg, CDialog)
	//{{AFX_MSG_MAP(CMyprojDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyprojDlg message handlers

BOOL CMyprojDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.
	m_List.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"可",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(1,"爱",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(2,"的",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(3,"测",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(4,"试",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(5,"不",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(6,"知",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(7,"怎",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(8,"么",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(9,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(10,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(11,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(12,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(13,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(14,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(15,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(16,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(17,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(18,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(19,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(20,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(21,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(22,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(23,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(24,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(25,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(26,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(27,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(28,"办",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(29,"办",LVCFMT_LEFT,100,0);


	m_List2.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_List2.InsertColumn(0,"可",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(1,"爱",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(2,"的",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(3,"测",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(4,"试",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(5,"不",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(6,"知",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(7,"怎",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(8,"么",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(9,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(10,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(11,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(12,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(13,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(14,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(15,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(16,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(17,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(18,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(19,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(20,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(21,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(22,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(23,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(24,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(25,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(26,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(27,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(28,"办",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(29,"办",LVCFMT_LEFT,100,0);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	char szBuf[100];
	GetConsoleTitle(szBuf,100);
	HWND hwnd = ::FindWindow(NULL,szBuf);
	HMENU hmenu = ::GetSystemMenu(hwnd,FALSE);
	::RemoveMenu(hmenu,SC_CLOSE,MF_BYCOMMAND);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyprojDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyprojDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyprojDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyprojDlg::OnOK() 
{
	// TODO: Add extra validation here
	e.Load("testdata1.xls");
	sheet1 = e.GetWorksheet("Sheet3");
	maxRows = sheet1->GetTotalRows();
	maxCols = sheet1->GetTotalCols();
	memset(data_label,0,maxRows);
	m_List.DeleteAllItems();
	for(size_t r=0;r<maxRows;++r)
	{	
		m_List.InsertItem(r,"");
		for(size_t c=0;c<maxCols;++c)
		{
			BasicExcelCell* cell = sheet1->Cell(r,c);	
			if (c == maxCols-1)
			{
				data_label[r]=cell->GetDouble();   //最后一列标签不显示而将其保存
			}
		
			CString str;
			switch (cell->Type())
			{
				case BasicExcelCell::UNDEFINED:
					str.Empty;
					break;
					
				case BasicExcelCell::INT:
					str.Format("%10d", cell->GetInteger());
					break;
					
				case BasicExcelCell::DOUBLE:
					str.Format("%5.2lf",cell->GetDouble());
					break;
					
				case BasicExcelCell::STRING:
					str.Format("%10s", cell->GetString());
					break;
					
				case BasicExcelCell::WSTRING:
					str.Format("%10s", cell->GetWString());
					break;
			}
				m_List.SetItemText(r,c,str);
				str.Empty();
		}
	}
}


void CMyprojDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	double idx[200];   //这个动态给内存 就炸 不知道为什么！弄了一下午没整明白
	int i=0;
	size_t cnn=0;   //计算有多少非空非0数据列
	size_t r=1;  //任取一行作为查找对象
	double stre=1;

	for (size_t c=0 ; c<maxCols-1 ; ++c)
	{
	//	CString str1;
		BasicExcelCell* cell=sheet1->Cell(r,c);
		switch (cell->Type())
		{
		case BasicExcelCell::UNDEFINED:
			{
				int stre=0;
				break;
			}	
		case BasicExcelCell::INT:
			{
				stre=cell->GetInteger();
				break;
			}
		case BasicExcelCell::DOUBLE:
			{
 				stre=cell->GetDouble();
				break;
			}
		case BasicExcelCell::STRING:
			{
				CString str1;
				str1.Format("%10s",cell->GetString());
	//			int str=atoi(str1.GetBuffer(str1.GetLength()));
				stre=0;
				break;
			}
		case BasicExcelCell::WSTRING:
			{
//				str1.Format("%10s", cell->GetWString());
				stre=0;
				break;
			}
		}
		//str1.Empty();
		if (stre == 0 || ( (stre >= -0.0000001) && (stre <= 0.0000001)))
		{
			idx[i]=0;
			++i;
		}
		else
		{
			idx[i]=1;
			++i;
			++cnn;
		}
	}
  
	
	m_List.DeleteAllItems();
	vector<vector<double> > data(maxRows,vector<double>(cnn,0));
	for (r=0 ; r<maxRows ; ++r)
	{
		int count=0;
		double temp;
		m_List.InsertItem(r,"");
		for(c=0 ; c<maxCols ; ++c)
		{
			if ( idx[c] == 1)
			{
				BasicExcelCell* cell1 = sheet1->Cell(r,c);	
				CString str2;
				switch (cell1->Type())
				{
				case BasicExcelCell::UNDEFINED:
					str2.Empty;
					break;
					
				case BasicExcelCell::INT:
					str2.Format("%10d", cell1->GetInteger());
					break;
					
				case BasicExcelCell::DOUBLE:
					str2.Format("%5.2lf",cell1->GetDouble());
					temp=cell1->GetDouble();
					break;
					
				case BasicExcelCell::STRING:
					str2.Format("%10s", cell1->GetString());
					break;
					
				case BasicExcelCell::WSTRING:
					str2.Format("%10s", cell1->GetWString());
					break;
				}
				m_List.SetItemText(r,count,str2);
				str2.Empty();
				data[r][count]=temp;
				count++;
			}

		}
	}

	//计算相关系数矩阵
	PCA_Demension init_data;
	vector<vector<double > > Show_data(maxRows,vector<double>(cnn,0));  //经过归一化的数据  用于同步操作显示
	init_data.PCA_demension(data,Show_data); 
/*
	m_List.DeleteAllItems();
	for (i=0 ; i<maxRows ; i++)
	{
		m_List.InsertItem(i,"");
		
		for (int j=0;j<init_data.Cols;j++)  //<=
		{
			CString str_cor;
			str_cor.Format("%f",Show_data[i][j]);  //
			m_List.SetItemText(i,j,str_cor);
			str_cor.Empty();
		}
	}


	//显示相关系数
	m_List.DeleteAllItems();
	CString str_cor;
	for (i=0 ; i<init_data.Cols ; ++i)
	{
		m_List.InsertItem(i,"");
		for (int j=0; j<init_data.Cols ; ++j)
		{
			str_cor.Format("%f",init_data.correlation[i][j]);
			m_List.SetItemText(i,j,str_cor);
			str_cor.Empty();
		}
	}
*/

	//关系矩阵 corre
	double *corre = new double[init_data.Cols * init_data.Cols];
	double *pdb_Vect = new double[init_data.Cols * init_data.Cols];
	double *pdb_EigenValues= new double[init_data.Cols];
	for (i =0; i<init_data.Cols;i++)
	{
		for (int j=0;j<init_data.Cols;j++)
		{
			corre[i*init_data.Cols+j]=init_data.correlation[i][j];
		}
	}


	init_data.JacbiCor(corre,init_data.Cols,pdb_Vect,Show_data,pdb_EigenValues,0.000001,500);   //把特征值全部去绝对值 并按照关系特征值排序
	memset(jacbi_ord_Dlg,0,init_data.Cols);
	for(i=0 ;i<init_data.Cols;i++)
	{
		jacbi_ord_Dlg[i]=init_data.jacbi_ord[i];
	}

/*
	//显示关系数矩阵的特征向量和特征值
	m_List.DeleteAllItems();
	for (i=0 ; i<=init_data.Cols ; i++)
	{
		m_List.InsertItem(i,"");
		if(i<init_data.Cols) //特征向量
		{
			for (int j=0;j<init_data.Cols;j++)
			{
				str_cor.Format("%f",pdb_Vect[i*init_data.Cols+j]);  //
				m_List.SetItemText(i,j,str_cor);
				str_cor.Empty();
			}
		}
		if(i==init_data.Cols) //特征值
		{
			for(int j=0;j<init_data.Cols;j++)
			{
				str_cor.Format("%f",pdb_EigenValues[j]);
				m_List.SetItemText(i,j,str_cor);
				str_cor.Empty();
			}
		}
	}
*/

	//PCA利用相关系数的特征值选择降纬

	double Final_Vects[100000];
	double Final_Eigen[200];
	memset(Final_Eigen,0,init_data.Cols);
	memset(Final_Vects,0,init_data.Cols * init_data.Cols);
	init_data.PCA_select(pdb_Vect,pdb_EigenValues,Show_data,(int)init_data.Cols,0.85,&nvar,Final_Vects,Final_Eigen);



	//显示PCA结果  显示的是最终筛选完的信息量最大的属性
	m_List.DeleteAllItems();
	for (i=0 ; i<maxRows ;i++)
	{
		m_List.InsertItem(i,"");
		for (int j=0;j<nvar;j++) //显示特征向量 var从1开始计数
		{
			CString str_cor;
		    str_cor.Format("%f",Show_data[i][j]);
			m_List.SetItemText(i,j,str_cor);
			str_cor.Empty();
		}		
	}


	//决策树C4.5
	attr_num=init_data.att_num;

	vector<vector<double> > rules(init_data.rule_num,vector<double>(init_data.att_num+1,0));
	for (  i=0;i<init_data.rule_num;i++)
	{
		for (int j=0; j<=init_data.att_num;j++)
		{
			if (j<=init_data.att_num-1)
			{
				rules[i][j] = Show_data[i][j];
			}
			else
			{
				rules[i][j] = data_label[i];
			}
		}
	} //还原数据标签
	
	m_List.DeleteAllItems();
	for (i=0 ; i<maxRows ;i++)
	{
		m_List.InsertItem(i,"");
		for (int j=0;j<nvar+1;j++) //显示特征向量 var从1开始计数
		{
			CString str_cor;
			str_cor.Format("%f",rules[i][j]);
			m_List.SetItemText(i,j,str_cor);
			str_cor.Empty();
		}		
	}



	init_data.build_decision_tree(rules,tree);
	printf("测试用例\n");
	init_data.print_tree(tree,0);

}

void CMyprojDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMyprojDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	e2.Load("testdata1.xls");
	sheet2 = e2.GetWorksheet("Sheet2");
	maxRows = sheet2->GetTotalRows();
	maxCols = sheet2->GetTotalCols();
	memset(test_label,0,maxRows);
	m_List2.DeleteAllItems();
	for(size_t r=0;r<maxRows;++r)
	{	
		m_List2.InsertItem(r,"");
		for(size_t c=0;c<maxCols;++c)
		{
			BasicExcelCell* cell = sheet2->Cell(r,c);	
			if (c == maxCols-1)
			{
				test_label[r]=cell->GetDouble();   //最后一列标签不显示而将其保存
			}
			
			CString str;
			switch (cell->Type())
			{
			case BasicExcelCell::UNDEFINED:
				str.Empty;
				break;
				
			case BasicExcelCell::INT:
				str.Format("%10d", cell->GetInteger());
				break;
				
			case BasicExcelCell::DOUBLE:
				str.Format("%5.2lf",cell->GetDouble());
				break;
				
			case BasicExcelCell::STRING:
				str.Format("%10s", cell->GetString());
				break;
				
			case BasicExcelCell::WSTRING:
				str.Format("%10s", cell->GetWString());
				break;
			}
			m_List2.SetItemText(r,c,str);
			str.Empty();
		}
	}
}

void CMyprojDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	double idx[200];   //这个动态给内存 就炸 不知道为什么！弄了一下午没整明白
	int i=0;
	size_t cnn=0;   //计算有多少非空非0数据列
	size_t r=1;  //任取一行作为查找对象
	double stre=1;

	for (size_t c=0 ; c<maxCols-1 ; ++c)
	{
	//	CString str1;
		BasicExcelCell* cell=sheet2->Cell(r,c);
		switch (cell->Type())
		{
		case BasicExcelCell::UNDEFINED:
			{
				int stre=0;
				break;
			}	
		case BasicExcelCell::INT:
			{
				stre=cell->GetInteger();
				break;
			}
		case BasicExcelCell::DOUBLE:
			{
 				stre=cell->GetDouble();
				break;
			}
		case BasicExcelCell::STRING:
			{
				CString str1;
				str1.Format("%10s",cell->GetString());
	//			int str=atoi(str1.GetBuffer(str1.GetLength()));
				stre=0;
				break;
			}
		case BasicExcelCell::WSTRING:
			{
//				str1.Format("%10s", cell->GetWString());
				stre=0;
				break;
			}
		}
		//str1.Empty();
		if (stre == 0 || ( (stre >= -0.0000001) && (stre <= 0.0000001)))
		{
			idx[i]=0;
			++i;
		}
		else
		{
			idx[i]=1;
			++i;
			++cnn;
		}
	}
  
	
	m_List2.DeleteAllItems();
	vector<vector<double> > data(maxRows,vector<double>(cnn,0));
	for (r=0 ; r<maxRows ; ++r)
	{
		int count=0;
		double temp;
		m_List2.InsertItem(r,"");
		for(c=0 ; c<maxCols ; ++c)
		{
			if ( idx[c] == 1)
			{
				BasicExcelCell* cell1 = sheet2->Cell(r,c);	
				CString str2;
				switch (cell1->Type())
				{
				case BasicExcelCell::UNDEFINED:
					str2.Empty;
					break;
					
				case BasicExcelCell::INT:
					str2.Format("%10d", cell1->GetInteger());
					break;
					
				case BasicExcelCell::DOUBLE:
					str2.Format("%5.2lf",cell1->GetDouble());
					temp=cell1->GetDouble();
					break;
					
				case BasicExcelCell::STRING:
					str2.Format("%10s", cell1->GetString());
					break;
					
				case BasicExcelCell::WSTRING:
					str2.Format("%10s", cell1->GetWString());
					break;
				}
				m_List2.SetItemText(r,count,str2);
				str2.Empty();
				data[r][count]=temp;
				count++;
			}

		}
	}

	//计算相关系数矩阵
	PCA_Demension init_data1;
	vector<vector<double > > Show_data(maxRows,vector<double>(cnn,0));  //经过归一化的数据  用于同步操作显示
	init_data1.PCA_demension(data,Show_data); 
/*
	//关系矩阵 corre
	double *corre = new double[init_data.Cols * init_data.Cols];
	double *pdb_Vect = new double[init_data.Cols * init_data.Cols];
	double *pdb_EigenValues= new double[init_data.Cols];
	for (i =0; i<init_data.Cols;i++)
	{
		for (int j=0;j<init_data.Cols;j++)
		{
			corre[i*init_data.Cols+j]=init_data.correlation[i][j];
		}
	}

	init_data.JacbiCor(corre,init_data.Cols,pdb_Vect,Show_data,pdb_EigenValues,0.000001,500);   //把特征值全部去绝对值 并按照关系特征值排序
	

	//PCA利用相关系数的特征值选择降纬
 	int nvar=0;
	double Final_Vects[100000];
	double Final_Eigen[200];
	memset(Final_Eigen,0,init_data.Cols);
	memset(Final_Vects,0,init_data.Cols * init_data.Cols);
	init_data.PCA_select(pdb_Vect,pdb_EigenValues,Show_data,(int)init_data.Cols,0.85,&nvar,Final_Vects,Final_Eigen);
*/

	//将测试数据按照训练样本训练好的特征值顺序排列并取前.85列
		


	vector<vector<double> > rules(init_data1.rule_num,vector<double>(attr_num+1,0));
	for (  i=0;i<init_data1.rule_num;i++)
	{
		for (int j=0; j<=nvar;j++)
		{
			if (j<=nvar-1)
			{
				rules[i][j] = Show_data[i][jacbi_ord_Dlg[j]];
			}
			else
			{
				rules[i][j] = test_label[i];
			}
		}
	} //还原数据标签
	
	m_List2.DeleteAllItems();
	for (i=0 ; i<maxRows ;i++)
	{
		m_List2.InsertItem(i,"");
		for (int j=0;j<nvar+1;j++) //显示特征向量 var从1开始计数
		{
			CString str_cor;
			str_cor.Format("%f",rules[i][j]);
			m_List2.SetItemText(i,j,str_cor);
			str_cor.Empty();
		}		
	}

	//显示预测值
	predict(tree,rules,0);

}

void CMyprojDlg::predict(Tree tree,vector<vector<double> > rules,int dex)
{
	if(!tree.branches.empty())  //不是叶子结点
	{
		
		for(int i=0;i<tree.branches.size()-1;i++)
		{
			for(int j=0;j<rules.size();j++)
			{
				if(rules[j][tree.root] <= tree.branches[i] )
				{
					predict(tree.children[i],rules,j);	
				}
				else
					predict(tree.children[i+1],rules,j);
			}
		}
	}
	else
	{
		//输出root
		CString str_cor;
		str_cor.Format("%d",tree.root);
		m_List2.SetItemText(dex,attr_num+1,str_cor);
		str_cor.Empty();
	}
}
