
// WxMoreInstanceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WxMoreInstance.h"
#include "WxMoreInstanceDlg.h"
#include "../InjectDll/InjectDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL checkMutex();
BOOL checkEvent();
void checkInstance();

HANDLE mutex;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWxMoreInstanceDlg �Ի���




CWxMoreInstanceDlg::CWxMoreInstanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWxMoreInstanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWxMoreInstanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWxMoreInstanceDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWxMoreInstanceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_MORE, &CWxMoreInstanceDlg::OnBnClickedBtnMore)
	ON_BN_CLICKED(IDC_BUTTON_ADVANCE, &CWxMoreInstanceDlg::OnBnClickedButtonAdvance)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CWxMoreInstanceDlg ��Ϣ�������

BOOL CWxMoreInstanceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	checkInstance();		//�����Լ��ĳ���ȥ�ģ���΢��û���κι�ϵ
	m_MessageHandleUI.Init();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWxMoreInstanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWxMoreInstanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWxMoreInstanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWxMoreInstanceDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ɱ�����
	StartHook();	//��������
}

BOOL checkMutex(){
	mutex = ::CreateMutex(NULL,FALSE,L"_WeChat_App_Instance_Identity_Mutex_Name1");
	int err = GetLastError();
	if (err == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, _T("already exist"), _T("ERROR"), SW_NORMAL);
		return FALSE;
	}
	return TRUE;
}


void checkInstance(){

	if(!checkMutex()){
		MessageBox(NULL, _T("�Ѿ����˵�������Ҫ�˳�����"), _T("ERROR"), SW_NORMAL);
		ExitProcess(0);
	}else{
		
		//CloseHandle(mutex);
		//OpenMutex(NULL, FALSE, )
	}
}
void CWxMoreInstanceDlg::OnBnClickedBtnMore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(m_hWnd, _T("open"), _T("http://www.xiaoyutang.net/toptic/%e5%be%ae%e4%bf%a1/pc%e5%be%ae%e4%bf%a1%e5%a4%9a%e5%bc%80%e6%9c%80%e6%96%b0%e4%bb%a3%e7%a0%81%e3%80%90%e5%85%bc%e5%ae%b9%e6%80%a7%e9%9d%9e%e5%b8%b8%e9%ab%98%e3%80%91/"), NULL, NULL, SW_SHOWNORMAL);	//��������
}

//�߼��汾������tab��������΢�Ź���
//����߼���
//1������������Ի���
//2������������ʾ�߼�tab����
//3��ͬʱ����hook���ܣ�Ȼ���ʼ��΢��hook��������
void CWxMoreInstanceDlg::OnBnClickedButtonAdvance()
{
	if(!IsWindow(m_tab_ui.GetSafeHwnd())){
		m_tab_ui.Create(m_tab_ui.IDD, GetDesktopWindow());
		m_MessageHandleUI.SetWechatTabUI(m_tab_ui.GetSafeHwnd());
		m_tab_ui.ShowWindow(SW_SHOW);
	}

	if(!m_tab_ui.IsWindowVisible()){
		m_tab_ui.ShowWindow(SW_SHOW);
	}
}


void CWxMoreInstanceDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//AfxMessageBox(L"hello world");
	CDialog::OnLButtonDown(nFlags, point);
}
