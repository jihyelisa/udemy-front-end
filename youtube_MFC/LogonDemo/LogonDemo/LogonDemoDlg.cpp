
// LogonDemoDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "LogonDemo.h"
#include "LogonDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogonDemoDlg 대화 상자




CLogonDemoDlg::CLogonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogonDemoDlg::IDD, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
	, m_bAuto(TRUE)
	, m_bUpdate(FALSE)
	, m_bSystem(FALSE)
	, m_strInput(_T(""))
	, m_str_selected(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLogonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Edit_ID, m_strID);
	DDX_Text(pDX, IDC_Edit_Password, m_strPassword);
	DDX_Check(pDX, IDC_Check_Auto, m_bAuto);
	DDX_Check(pDX, IDC_Check_Update, m_bUpdate);
	DDX_Check(pDX, IDC_Check_System, m_bSystem);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_Edit_Input, m_strInput);
	DDX_Text(pDX, IDC_Static_Selected, m_str_selected);
	DDX_Control(pDX, IDC_Spin_Value, m_spin);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(CLogonDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_Edit_ID, &CLogonDemoDlg::OnEnChangeEditId)
	ON_BN_CLICKED(IDOK, &CLogonDemoDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CLogonDemoDlg::OnNMClickSyslink1)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogonDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_Check_Auto, &CLogonDemoDlg::OnBnClickedCheckAuto)
	ON_BN_CLICKED(IDC_Button_Insertstring, &CLogonDemoDlg::OnBnClickedButtonInsertstring)
	ON_BN_CLICKED(IDC_Button_Addstring, &CLogonDemoDlg::OnBnClickedButtonAddstring)
	ON_BN_CLICKED(IDC_Button_delete, &CLogonDemoDlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_Button_Find, &CLogonDemoDlg::OnBnClickedButtonFind)
	ON_LBN_SELCHANGE(IDC_LIST1, &CLogonDemoDlg::OnLbnSelchangeList1)
	ON_EN_UPDATE(IDC_EDIT1, &CLogonDemoDlg::OnUpdateEditValue)
END_MESSAGE_MAP()


// CLogonDemoDlg 메시지 처리기

BOOL CLogonDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 체크박스 비활성화
	GetDlgItem(IDC_Check_Update)->EnableWindow(FALSE);
	GetDlgItem(IDC_Check_System)->EnableWindow(FALSE);

	// 프로그레스 컨트롤 초기화
	m_progress.SetRange(0, 100);
	m_progress.SetPos(50);

	// 스핀 컨트롤 초기화
	m_spin.SetRange(0, 100);
	m_spin.SetPos(50);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLogonDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLogonDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLogonDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLogonDemoDlg::OnEnChangeEditId()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLogonDemoDlg::OnBnClickedOk()
{
	UpdateData(); // edit control에 입력된 데이터를 연결된 변수에 할당해줌
	CString strTmp = _T("");
	strTmp.Format(_T("입력한 ID는 \"%s\"이며 암호는 \"%s\"입니다."),
					m_strID, m_strPassword);
	AfxMessageBox(strTmp);


	CDialogEx::OnOK();
}


void CLogonDemoDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString strUrl = _T("");
	CLinkCtrl* pLinkCtrl = (CLinkCtrl*)GetDlgItem(IDC_SYSLINK1);
	pLinkCtrl->GetItemUrl(0, strUrl);

	::ShellExecute(NULL, TEXT("open"), strUrl, NULL, NULL, SW_SHOW);

	*pResult = 0;
}


void CLogonDemoDlg::OnBnClickedButton1()
{
	m_bAuto = FALSE;
	m_bUpdate = TRUE;
	m_bSystem = TRUE;

	UpdateData(FALSE); // 입력값을 변수에 할당x 반대로 변수값을 입력란에 적용
}


void CLogonDemoDlg::OnBnClickedCheckAuto()
{
	UpdateData(); // 현재 체크박스 정보와 변수값 일치시킴

	if (m_bAuto)
	{
		GetDlgItem(IDC_Check_Update)->EnableWindow(FALSE);
		GetDlgItem(IDC_Check_System)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_Check_Update)->EnableWindow(TRUE);
		GetDlgItem(IDC_Check_System)->EnableWindow(TRUE);
	}
}


void CLogonDemoDlg::OnBnClickedButtonInsertstring()
{
	UpdateData();
	m_List.InsertString(0, m_strInput);
	
	m_strInput = _T("");
	UpdateData(FALSE);
}


void CLogonDemoDlg::OnBnClickedButtonAddstring()
{
	UpdateData();
	m_List.AddString(m_strInput);
	
	m_strInput = _T("");
	UpdateData(FALSE);
}


void CLogonDemoDlg::OnBnClickedButtondelete()
{
	int selectedIndex = m_List.GetCurSel();

	if (selectedIndex != -1)
		m_List.DeleteString(selectedIndex);
}


void CLogonDemoDlg::OnBnClickedButtonFind()
{
	UpdateData();

	CString strTmp = _T(""), strFind = _T("");
	int nIndex = m_List.FindString(-1, m_strInput);
	
	if (nIndex != LB_ERR)
	{
		m_List.SetCurSel(nIndex);
		m_List.GetText(nIndex, strFind);
		strTmp.Format(_T("%d:%s"), nIndex, strFind);
		AfxMessageBox(strTmp);
	}
	else
	{
		AfxMessageBox(_T("일치하는 항목을 찾을 수 없습니다."));
	}
}


void CLogonDemoDlg::OnLbnSelchangeList1()
{
	int nIndex = m_List.GetCurSel();
	CString selectedText;
	m_List.GetText(nIndex, selectedText);

	m_str_selected = selectedText;
	UpdateData(FALSE);
}


void CLogonDemoDlg::OnUpdateEditValue()
{
	if (m_spin.GetSafeHwnd())
	{
		int nPos = m_spin.GetPos();
		m_progress.SetPos(nPos);
	}
}
