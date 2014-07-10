
// UpdateT123Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define  RECBUFSIZE 1024
#define t123_dfu_offset (0X4000)
#define PRESIZE	(200)
/*----------------------------------------------------------*/
/*
*	枚举相关
*/
enum node
{
	Node_COM = 1,
};

enum eWhatUpdate
{
	Update_Code = 1,
	Update_Resource,
	Update_ALL,
	Update_Patch
};


enum eUpdateState
{
	Update_None = 0,
	Update_Init,
	Update_Init_Wait,
	Update_Config,
	Update_Config_Wait,
	Update_Ease = 5,
	Update_Ease_Wait,
	Update_Frame,
	Update_Frame_Wait = 8,
	Update_Frame_Finsh,
	Update_Frame_Finsh_Wait,
	Update_CheckSum,
	Update_CheckSum_Wait,
	Update_Free,

};

enum eRecT123State
{
	T123_None = 0,
	T123_Init_OK,
	T123_Config_OK,
	T123_Ease_OK,
	T123_Frame_OK,
	T123_Frame_Finsh_OK,
	Update_CheckSum_OK,

};

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
	CFile m_DebugFile;
	char  m_DebugMsgBuf[1000];
private:
	afx_msg BOOL ReadConfigFile(void);
	afx_msg BOOL OpenUartCom(void);//打开通信串口
	afx_msg void ReadUartCom(BYTE *p,UINT32 Len);
	afx_msg void WriteUartCom(BYTE *p,UINT32 Len);
	afx_msg void CloseUartCom(void);
	afx_msg BOOL InitDCB(void);
	afx_msg BOOL InitCommTimeouts(void);
	afx_msg HANDLE CreateCommThread(void);
	static DWORD WINAPI ThreadCommProc(LPCVOID pContext);


/*----------------------------------------------------------*/
/*
*	升级相关
*/
private:

	CComboBox m_ComboBoxUpdateType;
	CProgressCtrl m_ProgressCtrlUpdate;
	
	UINT32 m_UpdateFileLength;
	UINT32 m_UpdataFrameCount;
	BYTE m_UpdataFrameMsg[300];
	BYTE *m_pUpdateFileBuf;

	char m_UpdateConfigMsg[64];
	UINT m_UpdateConfigMsgLen;
	BYTE m_UpdateT123Type;
	UINT16 m_UpdateT123CheckCrc;
	UINT32 m_UpdateT123Time;


	DWORD	m_UpdateFlag;
	DWORD   m_TextAddr;
	DWORD   m_TextSize;;
	DWORD   m_UdataAddr;
	DWORD   m_UdataSize;
	DWORD   m_ResAddr;
	DWORD   m_ResSize;

	unsigned short m_TextCrc;

	unsigned short m_crcWrite;
	unsigned long m_tmpAddr;//xx
	unsigned long m_progAddr;
	unsigned char m_crcmethod;
	unsigned char m_ProgType;
	unsigned long m_fSize;
private:
	afx_msg void OnBnClickedButtonOpenUpdateFile();
	afx_msg void OnBnClickedButtonProgram();
	afx_msg void ByteOrderSwap(unsigned char* in, unsigned char* out, int size);
	afx_msg void ByteHexToCharConver(BYTE *in,UINT Len);
	afx_msg void UpdateProgress(UINT Progress);
	/*
	*	通信协议相关
	*/

	BOOL m_bKillMainProcThread;
	HANDLE m_hMainThread;
	HANDLE m_hMainEvent;

	BYTE m_FlybtSendBuf[1024];
	BYTE m_FrameStatus;
	BYTE m_FrameLen;
	BYTE m_FrameLenMax;
	BYTE m_FrameCheckSum;
	BYTE m_FrameRecBuf[256];


	BYTE m_UpdateFileStatus;
	BYTE m_RecT123UpdateStatus;
	UINT32 m_CheckUpdateFileRecStatusTime;
	static DWORD WINAPI ThreadMainUpdateFileProc(LPCVOID pContext);
	afx_msg void PrintUpdateFileCommandToLpc(BYTE *p,UINT Len);
	afx_msg void PrintUpdateInit(void);
	afx_msg void PrintUpdateConfigMsg(void);
	afx_msg void PrintUpdateEaseFlash(void);
	afx_msg void PrintUpdateFrameData(BYTE *p,UINT Len);
	afx_msg void PrintUpdateFrameFinish(void);
	afx_msg void PrintUpdateCheckSum(void);
	afx_msg void OnRecData(BYTE dat);
	afx_msg void OnRecCommand(BYTE *p,UINT Len);
	afx_msg void UpdateFileRecCommand(BYTE *p,UINT Len);
	
	

};
