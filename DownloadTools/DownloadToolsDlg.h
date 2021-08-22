
// DownloadToolsDlg.h: 头文件
//

#pragma once
#include "CIniFileEdit.h"

// CYP工具路径变量
#define CYP_PATH	("C:\\Program Files (x86)\\Cypress\\Cypress Auto Flash Utility 1.0")

class CiniFileEdit;

// CDownloadToolsDlg 对话框
class CDownloadToolsDlg : public CDialogEx
{
// 构造
public:
	CDownloadToolsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOADTOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 系统定时事件
	enum TimerEvent_Type
	{
		SYS_TICK_1Hz = 1000,
		TICK_10Hz = 100,
		TICK_100Hz = 10,
		TICK_1000Hz = 1,
	};

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedToolpathload();
	afx_msg void OnBnClickedFileload();
private:
	CIniFileEdit m_cfgFile;
	CString m_err;
	CString m_CypPath;
	CEdit m_ToolPath;
	CEdit m_FilePath;
	CRichEditCtrl m_MsgBox;
	CProgressCtrl m_Procress;
	void OnInitParam(void* param);
	void PostMsg(CString str, COLORREF col = RGB(150, 150, 150), BOOL bNewLine = FALSE);
	void OnSaveLog(CString path);
	CString ExecuteCmd(CString str);
	TCHAR* StringToChar(CString& str);
	void LoadIniCfgParam(void); // 加载INI本地配置文件
	void SaveIniCfgParam(); // 保持配置文件参数

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSavelog();
	afx_msg void OnBnClickedDownload();
	afx_msg void OnBnClickedClear();
	afx_msg void OnClose();
};
