
// UpdateT123Dlg.h : ͷ�ļ�
//

#pragma once

#define  RECBUFSIZE 1024

// CUpdateT123Dlg �Ի���
class CUpdateT123Dlg : public CDialogEx
{
// ����
public:
	CUpdateT123Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPDATET123_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
/*----------------------------------------------------------*/
/*
*	ö�����
*/
enum node
{
	Node_COM = 1,
};
/*----------------------------------------------------------*/
/*
*	�������
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
	afx_msg void OpenUartCom(void);//��ͨ�Ŵ���
	afx_msg void ReadUartCom(BYTE *p,UINT32 Len);
	afx_msg void WriteUartCom(BYTE *p,UINT32 Len);
	afx_msg void CloseUartCom(void);
	afx_msg BOOL InitDCB(void);
	afx_msg BOOL InitCommTimeouts(void);
	afx_msg HANDLE CreateCommThread(void);
	static DWORD WINAPI ThreadCommProc(LPCVOID pContext);
};
