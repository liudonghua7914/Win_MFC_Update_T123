
// UpdateT123Dlg.h : 头文件
//

#pragma once

#define  RECBUFSIZE 1024

// CUpdateT123Dlg 对话框
class CUpdateT123Dlg : public CDialogEx
{
// 构造
public:
	CUpdateT123Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPDATET123_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
/*----------------------------------------------------------*/
/*
*	枚举相关
*/
enum node
{
	Node_COM = 1,
};
/*----------------------------------------------------------*/
/*
*	串口相关
*/
private:
	DWORD m_BaudRate;       /* Baudrate at which running       */
	BYTE m_ByteSize;        /* Number of bits/byte, 4-8        */
	BYTE m_Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
	BYTE m_StopBits;        /* 0,1,2 = 1, 1.5, 2               */
	CString m_ComName;

	BOOL m_bHaveCloseComm;
	BOOL m_bKillCommThread;
	HANDLE m_hComm;	
	HANDLE m_hCommThread;
	OVERLAPPED m_ovRead;
	OVERLAPPED m_ovWrite;
	BYTE m_RecBuf[RECBUFSIZE];

	BYTE m_FlyConfigNode;
	CFile m_FlyConfigFile;
private:
	afx_msg BOOL ReadConfigFile(void);
	afx_msg void OpenUartCom(void);//打开通信串口
	afx_msg void ReadUartCom(BYTE *p,UINT32 Len);
	afx_msg void WriteUartCom(BYTE *p,UINT32 Len);
	afx_msg void CloseUartCom(void);
	afx_msg BOOL InitDCB(void);
	afx_msg BOOL InitCommTimeouts(void);
	afx_msg HANDLE CreateCommThread(void);
	static DWORD WINAPI ThreadCommProc(LPCVOID pContext);
};
