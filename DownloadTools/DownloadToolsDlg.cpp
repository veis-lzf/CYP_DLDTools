
// DownloadToolsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DownloadTools.h"
#include "DownloadToolsDlg.h"
#include "afxdialogex.h"
#include "CIniFileEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDownloadToolsDlg 对话框


CDownloadToolsDlg::CDownloadToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOWNLOADTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CDownloadToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ToolPath, m_ToolPath);
	DDX_Control(pDX, IDC_hexPath, m_FilePath);
	DDX_Control(pDX, IDC_Msg, m_MsgBox);
	DDX_Control(pDX, IDC_Progress, m_Procress);
}

BEGIN_MESSAGE_MAP(CDownloadToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ToolPathLoad, &CDownloadToolsDlg::OnBnClickedToolpathload)
	ON_BN_CLICKED(IDC_FileLoad, &CDownloadToolsDlg::OnBnClickedFileload)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SaveLog, &CDownloadToolsDlg::OnBnClickedSavelog)
	ON_BN_CLICKED(IDC_Download, &CDownloadToolsDlg::OnBnClickedDownload)
	ON_BN_CLICKED(IDC_Clear, &CDownloadToolsDlg::OnBnClickedClear)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDownloadToolsDlg 消息处理程序
BOOL CDownloadToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	OnInitParam(NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDownloadToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CDownloadToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDownloadToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDownloadToolsDlg::OnBnClickedToolpathload()
{
	static TCHAR BASED_CODE szFilter[] = 
		_T("hex Files (*.exe)|*.exe|")
		_T("All Files (*.*)|*.*||");

	CString filePath;
	LPCTSTR filename = NULL; // 打开的文件路径
	m_ToolPath.GetWindowText(filePath);
	if (!filePath.IsEmpty())
		filename = (LPCTSTR)filePath.GetString();

	CFileDialog dlg(
		TRUE, NULL, filename,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		szFilter, 
		NULL, 0, TRUE);

	INT_PTR ret = dlg.DoModal();
	if (ret == IDCANCEL)
		return;

	CString szPath = dlg.GetPathName();
	m_ToolPath.SetWindowText(szPath.GetString());

}

/**
  *  加载需要下载的程序文件
  */
void CDownloadToolsDlg::OnBnClickedFileload()
{
	static TCHAR BASED_CODE szFilter[] =
		_T("hex Files (*.hex)|*.hex|")
		_T("bin Files (*.bin)|*.bin|")
		_T("All Files (*.*)|*.*||");

	CString filePath;
	LPCTSTR filename = NULL; // 打开的文件路径
	m_FilePath.GetWindowText(filePath);
	if (!filePath.IsEmpty())
		filename = (LPCTSTR)filePath.GetString();

	CFileDialog dlg(
		TRUE, NULL, filename,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL, 0, TRUE);

	INT_PTR ret = dlg.DoModal();
	if (ret == IDCANCEL)
		return;

	CString szPath = dlg.GetPathName();
	m_FilePath.SetWindowText(szPath.GetString());
	CButton *pBtn = (CButton*)GetDlgItem(IDC_Download);
	if (pBtn != NULL)
		pBtn->EnableWindow();
}

/**
  * 界面控件初始化入口函数
  */
void CDownloadToolsDlg::OnInitParam(void* param)
{
	LoadIniCfgParam(); // 加载配置文件参数

	// 初始化进度条
	m_Procress.SetRange32(0, 3000);
	m_Procress.SetBarColor(RGB(0, 0, 255));
	m_Procress.SetStep(1);
	m_Procress.SetPos(0);
	
	CButton* pBtn = (CButton*)GetDlgItem(IDC_Download);
	CString str;
	m_FilePath.GetWindowText(str);
	if (str.IsEmpty())
	{
		if (pBtn != NULL)
			pBtn->EnableWindow(FALSE);
	}

	m_FilePath.EnableWindow(FALSE);
	m_ToolPath .EnableWindow(FALSE);
}

/*
 * 从本地ini配置文件加载参数
 **/
void CDownloadToolsDlg::LoadIniCfgParam()
{
	CString szToolPath, szFilePath;
	m_cfgFile.SetFileHandle(_T("./DownloadConfig.ini"));
	CIniFileEdit::CfgStrStruct cfg;
	cfg.lpAppName = _T("PATH");
	cfg.lpString = NULL;
	cfg.lpFileName = NULL;

	cfg.lpKeyName = _T("toolpath");
	m_cfgFile.GetProfileString(&cfg, szToolPath);

	cfg.lpKeyName = _T("filepath");
	m_cfgFile.GetProfileString(&cfg, szFilePath);

	cfg.lpKeyName = _T("CYP_PATH");
	DWORD nRet = m_cfgFile.GetProfileString(&cfg, m_CypPath);
	if (nRet <= 0)
		m_CypPath = CYP_PATH; // 如果配置文件里面得不到CYP路径，则默认初始化为CYP_PATH宏

	// 初始化界面显示
	m_ToolPath.SetWindowText(szToolPath);
	m_FilePath.SetWindowText(szFilePath);

	m_MsgBox.SetBackgroundColor(FALSE, RGB(0, 0, 0));
}

/*
 * 保存工具路径及程序路径到本地INI文件
 **/
void CDownloadToolsDlg::SaveIniCfgParam()
{
	CString szToolPath, szFilePath;
	CIniFileEdit::CfgStrStruct cfg;
	cfg.lpAppName = _T("PATH");
	cfg.lpString = NULL;
	cfg.lpFileName = NULL;

	m_ToolPath.GetWindowText(szToolPath);
	cfg.lpKeyName = _T("toolpath");
	cfg.lpString = szToolPath.GetString();
	m_cfgFile.SetProfileString(&cfg);

	m_FilePath.GetWindowText(szFilePath);
	cfg.lpKeyName = _T("filepath");
	cfg.lpString = szFilePath.GetString();
	m_cfgFile.SetProfileString(&cfg);

	cfg.lpKeyName = _T("CYP_PATH");
	cfg.lpString = m_CypPath;
	m_cfgFile.SetProfileString(&cfg);
}

void CDownloadToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case SYS_TICK_1Hz:
	{
		// 1Hz处理函数
	}
	break;

	case TICK_10Hz:
	{
		// 10Hz处理函数
	}
	break;

	case TICK_100Hz:
	{
		// 100Hz处理函数
	}
	break;

	case TICK_1000Hz:
	{
		// 1000Hz处理函数
		m_Procress.StepIt();
	}
	break;

	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

/*
 * 输出log信息到richedit编辑框
 * 参数：
 *		【str】显示的内容
 *		【col】显示的颜色，缺省黑色
 *		【bNewLine】输出完成后是否换行，TRUE：换行，FLASE：不换行，缺省FALSE
 **/
void CDownloadToolsDlg::PostMsg(CString str, COLORREF col, BOOL bNewLine)
{
	CHARFORMAT cf;
	
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cf.dwEffects = 0;
	cf.yHeight = 10 * 24; // 文字高度
	cf.crTextColor = col; // 文字颜色
	_tccpy(cf.szFaceName, _T("黑体")); // 设置字体

	m_MsgBox.SetSelectionCharFormat(cf);
	m_MsgBox.ReplaceSel(str);

	if(bNewLine)
		m_MsgBox.ReplaceSel(_T("\r\n"));

	for (int i = 0; i < m_MsgBox.GetLineCount(); ++i)
		m_MsgBox.LineScroll(LineScroll_STEP);
}

/*
 * log文件流输出回调函数
 **/
static DWORD CALLBACK LogStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	CFile* pFile = (CFile*)dwCookie;

	pFile->Write(pbBuff, cb);
	*pcb = cb;
	return 0;
}

/*
 * log文件流输出格式设置（支持普通文本格式和rtf格式）
 * 参数：
 *		【path】文件名称及路径
 **/
void CDownloadToolsDlg::OnSaveLog(CString path)
{
	if (path.Find(_T(".")) == -1)
		path += _T(".rtf");

	CFile cFile(path, CFile::modeCreate | CFile::modeWrite);
	EDITSTREAM es;

	es.dwCookie = (DWORD)&cFile;
	es.pfnCallback = LogStreamOutCallback; // 注册回调函数

	int nPos = path.ReverseFind('\\');
	CString fileName = path.Right(path.GetLength() - nPos - 1);
	nPos = fileName.ReverseFind('.');
	fileName = fileName.Right(fileName.GetLength() - nPos - 1);

	if(_tccmp(fileName, _T("rtf")) == 0)
		m_MsgBox.StreamOut(SF_RTF, es);
	else
		m_MsgBox.StreamOut(SF_TEXT, es);

	PostMsg(_T("日志保存成功！"), RGB(255, 0, 0), TRUE);
}

/*
 * 响应保存log按钮事件
 **/
void CDownloadToolsDlg::OnBnClickedSavelog()
{
	static TCHAR BASED_CODE szFilter[] =
		_T("hex Files (*.rtf)|*.rtf|")
		_T("All Files (*.*)|*.*||");

	CString date;
	COleDateTime tim = COleDateTime::GetCurrentTime();
	date = tim.Format(_T("%Y-%m-%d_%H-%M-%S"));

	CFileDialog dlg(
		FALSE, _T(".rtf"), date,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL, 0, TRUE);

	INT_PTR ret = dlg.DoModal();

	if (ret == IDCANCEL)
		return;

	CString szPath = dlg.GetPathName();
	OnSaveLog(szPath);
}

void CDownloadToolsDlg::OnBnClickedDownload()
{
	CString szCmd;
	CString ocdPath, filePath;
	m_ToolPath.GetWindowText(ocdPath);
	m_FilePath.GetWindowText(filePath);
	filePath.Replace(_T('\\'), _T('/'));
	
	szCmd.Format(_T("\"%s\" -s \"%s\\scripts\" -f interface\\jlink.cfg -c ")
		_T("\"transport select swd\" -f target\\traveo2_1m_0A.cfg -c \"program %s 0x0 verify exit\""),
		ocdPath.GetString(), CString(CYP_PATH), filePath.GetString());

	SetTimer(TICK_1000Hz, TICK_1000Hz, NULL);
	CString szOutput = ExecuteCmd(szCmd);

	COLORREF col;
	int ret = szOutput.Find(_T("Programming Finished"));
	if (-1 != ret)
		col = RGB(0, 255, 0);
	else
		col = RGB(255, 0, 0);

	if (szOutput.IsEmpty())
	{
		MessageBox(_T("请检查工具路径是否正常或工具是否安装！"), _T("提示"), MB_ICONWARNING);
		return;
	}
	
	// 输出下载日志
	PostMsg(szCmd, col, TRUE);
	PostMsg(szOutput, col, TRUE);

	int nlow = 0, nhigh = 0;
	m_Procress.GetRange(nlow, nhigh);
	KillTimer(TICK_1000Hz); // 关闭定时器
	if (-1 != ret)
	{
		m_Procress.SetPos(nhigh); // 设置进度条为满值
		PostMsg(CString("升级成功！\r\n"), col, TRUE);
		MessageBox(_T("升级成功！"), _T("提示"), MB_ICONINFORMATION);
	}
	else
	{
		PostMsg(CString("升级失败！\r\n"), col, TRUE);
		MessageBox(_T("升级失败，详情请查看日志窗口！"), _T("提示"), MB_ICONERROR);
	}
	m_Procress.SetPos(nlow);
}

// 执行cmd命令
CString CDownloadToolsDlg::ExecuteCmd(CString str)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead = NULL, hWrite = NULL;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		m_err = theApp.GetLastError(GetLastError());
		PostMsg(m_err, RGB(255, 0, 0), TRUE);
		return NULL;
	}

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	TCHAR* cmdline = StringToChar(str);
	BOOL ret = CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	// 进程释放句柄资源
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if (!ret)
	{
		m_err = theApp.GetLastError(GetLastError());
		PostMsg(m_err, RGB(255, 0, 0), TRUE);
		return NULL;
	}
	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer, 0, 4096);
	CString output;
	DWORD byteRead;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &byteRead, NULL) == NULL)
			break;

		buffer[byteRead] = '\0'; // 附加字符串结束标志
		output += buffer;
		memset(buffer, 0, byteRead); // 清除缓冲区，避免出现字符堆叠问题
	}
	
	CloseHandle(hRead);
	return output;
}

// 其中用到一个外部函数：void StringToChar(&str);
// 这个函数的作用是CString格式的命令转化为TCHAR格式
TCHAR* CDownloadToolsDlg::StringToChar(CString& str)
{
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}

// 清屏
void CDownloadToolsDlg::OnBnClickedClear()
{
	m_MsgBox.SetSel(0, -1);
	m_MsgBox.ReplaceSel(_T(""));
}


void CDownloadToolsDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SaveIniCfgParam();
	CDialogEx::OnClose();
}
