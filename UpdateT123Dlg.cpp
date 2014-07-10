
// UpdateT123Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpdateT123.h"
#include "UpdateT123Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char ch[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CUpdateT123Dlg 对话框




CUpdateT123Dlg::CUpdateT123Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateT123Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateT123Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxUpdateType);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrlUpdate);
}

BEGIN_MESSAGE_MAP(CUpdateT123Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdateT123Dlg::OnBnClickedButtonOpenUpdateFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CUpdateT123Dlg::OnBnClickedButtonProgram)
END_MESSAGE_MAP()


// CUpdateT123Dlg 消息处理程序

BOOL CUpdateT123Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	m_ComboBoxUpdateType.AddString(__T("Code"));
	m_ComboBoxUpdateType.AddString(__T("Resource"));
	m_ComboBoxUpdateType.AddString(__T("All"));

	m_ComboBoxUpdateType.SetCurSel(2);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpdateT123Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpdateT123Dlg::OnPaint()
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
HCURSOR CUpdateT123Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************************************************************************************************************************************
**函数名称:		ByteOrderSwap
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::ByteOrderSwap(unsigned char* in, unsigned char* out, int size)
{
	unsigned char temp[16];
	int i = 0;
	for(i = 0; i < size; i++)
	{
		temp[size-1-i] = in[i];
	}

	for(i = 0; i < size; i++)
	{
		out[i] = temp[i];
	}
}

/*********************************************************************************************************************************************
**函数名称:		ByteHexToCharConver
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::ByteHexToCharConver(BYTE *in,UINT Len)
{
	char tmpBuf[5] = {'\0'};
	UINT DebugCount = 0;
	BYTE tmpLen = 0;
	UINT i = 0;
	if (Len >= sizeof(m_DebugMsgBuf))
	{
		MessageBox(__T("DebugCount is too long"));
	}
	
	for (i = 0;i < Len;i++)
	{
		tmpBuf[0] = ch[in[i] / 16];
		tmpBuf[1] = ch[in[i] % 16];
		tmpBuf[2] = ' ';
		tmpBuf[3] = '\0';
		memcpy(&m_DebugMsgBuf[DebugCount],tmpBuf,3);
		DebugCount += 3;
	}
	memcpy(&m_DebugMsgBuf[DebugCount],"\n",strlen("\n"));
	DebugCount += 1;
	//m_DebugFile.Write(m_DebugMsgBuf,DebugCount);
}
/*********************************************************************************************************************************************
**函数名称:		UpdateProgress
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::UpdateProgress(UINT Progress)
{
	wchar_t wProCur[30] = {'\0'};
	int TmpProgress = m_fSize - Progress;
	memset(wProCur,'\0',sizeof(wProCur));
	_itow(Progress,wProCur,10);
	SetDlgItemText(IDC_EDIT4,wProCur);
	
	m_ProgressCtrlUpdate.SetPos(TmpProgress);
}
/*********************************************************************************************************************************************
**函数名称:		UpdateFileRecCommand
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::UpdateFileRecCommand(BYTE *p,UINT Len)
{
	CString cRes;
	switch (p[0])
	{
		case 0X00:	
					if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = T123_Init_OK;
					}
					else
					{
						cRes = "T123 Init Fail";
					}
					break;

		case 0X01:	if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = T123_Config_OK;
					}
					else
					{
						cRes = "T123 Config Fail";
					}
					break;

		case 0X02:	if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = T123_Ease_OK;
					}
					else
					{
						cRes = "T123 Ease Fail";
					}
					break;

		case 0X03:	if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = T123_Frame_OK;
					}
					else
					{
						cRes = "T123 Frame Fail";
					}
					break;

		case 0X04:	if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = T123_Frame_Finsh_OK;
					}
					else
					{
						cRes = "T123 Frame_Finsh Fail";
					}
					break;

		case 0x05:	if (0X01 == p[1])
					{
						m_RecT123UpdateStatus = Update_CheckSum_OK;
					}
					else
					{
						cRes = "T123 CheckSum Fail";
					}
					break;
		default:
					break;
	}


	if (!p[1])
	{
		MessageBox(cRes);
	}
}
/*********************************************************************************************************************************************
**函数名称:		OnRecCommand
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::OnRecCommand(BYTE *p,UINT Len)
{
	switch (p[0])
	{
		case 0X40:	UpdateFileRecCommand(&p[1],Len - 1);
					break;

		default:
					break;
	}
	SetEvent(m_hMainEvent);
}
/*********************************************************************************************************************************************
**函数名称:		OnRecData
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::OnRecData(BYTE data)
{
	
	switch(m_FrameStatus)
	{
		case 0:		if(0XFF == data)
					{
						m_FrameStatus = 1;
					}
					break;

		case 1:		if(0X55 == data)
					{
						m_FrameStatus = 2;
					}
					else
					{
						m_FrameStatus = 0;
					}
					break;

		case 2:		m_FrameLenMax = m_FrameCheckSum = data;
					m_FrameLen = 0;
					m_FrameStatus = 3;
					break;

		case 3:		if (m_FrameLen < m_FrameLenMax - 1)
					{
						m_FrameRecBuf[m_FrameLen] = data;
						m_FrameCheckSum += data;
						m_FrameLen++;
					}
					else
					{
						if (data == m_FrameCheckSum)
						{
							OnRecCommand(&m_FrameRecBuf[0],m_FrameLen - 1);	
						}
						else
						{
							m_FrameStatus = 0;
							m_FrameCheckSum = 0;	
						}
						m_FrameStatus = 0;
						m_FrameCheckSum = 0;
					}
					break;
	}
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateFileCommandToLpc
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateFileCommandToLpc(BYTE *p,UINT Len)
{
	UINT i;
	BYTE crc;
	crc = Len+1;
	
	m_FlybtSendBuf[0] =0XFF;
	m_FlybtSendBuf[1] =0X55;
	m_FlybtSendBuf[2] = Len + 1;
	
	for (i = 0;i < Len;i++)
	{
		m_FlybtSendBuf[3 + i] = p[i];
		crc += p[i];
		
	}
	m_FlybtSendBuf[3 + i] = crc;	
	WriteUartCom(m_FlybtSendBuf,Len + 4);
	ByteHexToCharConver(m_FlybtSendBuf,Len + 4);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateInit
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateInit(void)
{
	BYTE buf[] = {0X40,0X00,0X00};
	buf[2] = m_UpdateT123Type;
	PrintUpdateFileCommandToLpc(buf,3);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateConfigMsg
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateConfigMsg(void)
{
	BYTE buf[64] = {0X40,0X01,0X00};
		
	buf[2] = (m_UpdateFlag >> 0) & 0XFF;
	buf[3] = (m_UpdateFlag >> 8) & 0XFF;
	buf[4] = (m_UpdateFlag >> 16) & 0XFF;
	buf[5] = (m_UpdateFlag >> 24) & 0XFF;

	buf[6] = (m_TextAddr >> 0) & 0XFF;
	buf[7] = (m_TextAddr >> 8) & 0XFF;
	buf[8] = (m_TextAddr >> 16) & 0XFF;
	buf[9] = (m_TextAddr >> 24) & 0XFF;

	buf[10] = (m_TextSize >> 0) & 0XFF;
	buf[11] = (m_TextSize >> 8) & 0XFF;
	buf[12] = (m_TextSize >> 16) & 0XFF;
	buf[13] = (m_TextSize >> 24) & 0XFF;

	buf[14] = (m_UdataAddr >> 0) & 0XFF;
	buf[15] = (m_UdataAddr >> 8) & 0XFF;
	buf[16] = (m_UdataAddr >> 16) & 0XFF;
	buf[17] = (m_UdataAddr >> 24) & 0XFF;

	buf[18] = (m_UdataSize >> 0) & 0XFF;
	buf[19] = (m_UdataSize >> 8) & 0XFF;
	buf[20] = (m_UdataSize >> 16) & 0XFF;
	buf[21] = (m_UdataSize >> 24) & 0XFF;

	buf[22] = (m_ResAddr >> 0) & 0XFF;
	buf[23] = (m_ResAddr >> 8) & 0XFF;
	buf[24] = (m_ResAddr >> 16) & 0XFF;
	buf[25] = (m_ResAddr >> 24) & 0XFF;

	buf[26] = (m_ResSize >> 0) & 0XFF;
	buf[27] = (m_ResSize >> 8) & 0XFF;
	buf[28] = (m_ResSize >> 16) & 0XFF;
	buf[29] = (m_ResSize >> 24) & 0XFF;

	buf[30] = (m_crcWrite >> 0) & 0XFF;
	buf[31] = (m_crcWrite >> 8) & 0XFF;

	PrintUpdateFileCommandToLpc(buf,2 + 30);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateEaseFlash
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateEaseFlash(void)
{
	BYTE buf[] = {0X40,0X02,0X00};
	PrintUpdateFileCommandToLpc(buf,3);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateFrameData
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateFrameData(BYTE *p,UINT Len)
{
	m_UpdataFrameMsg[0] = 0X40;
	m_UpdataFrameMsg[1] = 0x03;
	memcpy(&m_UpdataFrameMsg[2],p,Len);
	PrintUpdateFileCommandToLpc(m_UpdataFrameMsg,Len + 2);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateFrameFinish
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateFrameFinish(void)
{
	BYTE buf[] = {0X40,0X04,0X00};
	PrintUpdateFileCommandToLpc(buf,3);
}
/*********************************************************************************************************************************************
**函数名称:		PrintUpdateCheckSum
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::PrintUpdateCheckSum(void)
{
	BYTE buf[] = {0X40,0X05,0X00};
	PrintUpdateFileCommandToLpc(buf,3);
}
/*********************************************************************************************************************************************
**函数名称:		OnBnClickedButtonOpenUpdateFile
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::OnBnClickedButtonOpenUpdateFile(void)
{
	// TODO: 在此添加控件通知处理程序代码
	CString cFilePatchName;
	CFileDialog UpdateFileDlg(TRUE);
	m_pUpdateFileBuf = NULL;
	UpdateFileDlg.m_ofn.lpstrFilter = __T("All File (*.*)\0*.*\0*.bin\0*.bin\0Text(*.txt)\0*.txt\0\0");
	if (IDOK  == UpdateFileDlg.DoModal())
	{
		cFilePatchName = UpdateFileDlg.GetPathName();
		SetDlgItemText(IDC_PATH,cFilePatchName);//显示文件路径
		CFile UpdateFile(cFilePatchName,CFile::modeRead);
		m_UpdateFileLength = UpdateFile.GetLength();
		
		if (NULL == m_pUpdateFileBuf)
		{
			m_pUpdateFileBuf = new BYTE[m_UpdateFileLength + 1];
		}

		if (NULL != m_pUpdateFileBuf)
		{
			UpdateFile.Read(m_pUpdateFileBuf,m_UpdateFileLength);
			m_pUpdateFileBuf[m_UpdateFileLength] = '\0';
		}
		else
		{
			MessageBox(__T("new m_pUpdateFileBuf 失败"));
		}

		m_UpdateConfigMsgLen = 4 * 7;
		UpdateFile.Seek(0X100 + t123_dfu_offset,CFile::begin);
		UpdateFile.Read(m_UpdateConfigMsg,m_UpdateConfigMsgLen);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
}
/*********************************************************************************************************************************************
**函数名称:		ThreadMainUpdateFileProc
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
DWORD WINAPI CUpdateT123Dlg::ThreadMainUpdateFileProc(LPCVOID pContext)
{
	CUpdateT123Dlg *pCUpdateT123Dlg = (CUpdateT123Dlg *)pContext;
	UINT FrameSize = 0;
	BYTE TmpUpdateFileStatus = Update_None;
	CString CstrStatus;
	UINT TmpUpdateT123Time = 0;
	wchar_t wMin[10];
	wchar_t wSec[10];
	CString cTime;

	while (!pCUpdateT123Dlg->m_bKillMainProcThread)
	{
		WaitForSingleObject(pCUpdateT123Dlg->m_hMainEvent,100);
		switch(pCUpdateT123Dlg->m_UpdateFileStatus)
		{
			case Update_None:
								break;	

			case Update_Init:	pCUpdateT123Dlg->PrintUpdateInit();
								pCUpdateT123Dlg->m_UpdateFileStatus = Update_Init_Wait;
								FrameSize = pCUpdateT123Dlg->m_fSize;
								pCUpdateT123Dlg->UpdateProgress(FrameSize);
								CstrStatus = "Init...";
								break;

			case Update_Init_Wait:
								if(T123_Init_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Config;
								}
								break;

			case Update_Config:	pCUpdateT123Dlg->PrintUpdateConfigMsg();
								pCUpdateT123Dlg->m_UpdateFileStatus = Update_Config_Wait;
								CstrStatus = "Config...";
								break;

			case Update_Config_Wait:
								if(T123_Config_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Ease;
								}
								break;

			case Update_Ease:	pCUpdateT123Dlg->PrintUpdateEaseFlash();
								pCUpdateT123Dlg->m_UpdateFileStatus = Update_Ease_Wait;
								CstrStatus = "Ease...";
								break;


			case Update_Ease_Wait:
								if(T123_Ease_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame;
								}
								break;

			case Update_Frame:	if (FrameSize / PRESIZE)
								{
									pCUpdateT123Dlg->PrintUpdateFrameData(&pCUpdateT123Dlg->m_pUpdateFileBuf[pCUpdateT123Dlg->m_UpdataFrameCount],PRESIZE);
									FrameSize -= PRESIZE;
									pCUpdateT123Dlg->m_UpdataFrameCount += PRESIZE;
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame_Wait;
								}
								else if (FrameSize % PRESIZE)
								{
									pCUpdateT123Dlg->PrintUpdateFrameData(&pCUpdateT123Dlg->m_pUpdateFileBuf[pCUpdateT123Dlg->m_UpdataFrameCount],FrameSize % PRESIZE);
									FrameSize = 0;
									pCUpdateT123Dlg->m_UpdataFrameCount += FrameSize % PRESIZE;
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame_Wait;
								}
								else
								{
									//发送完成
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame_Finsh;
								}
								pCUpdateT123Dlg->UpdateProgress(FrameSize);
								CstrStatus = "Update...";

								break;

			case Update_Frame_Wait:
								if (T123_Frame_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame;
								}
								break;

			case Update_Frame_Finsh:
								pCUpdateT123Dlg->PrintUpdateFrameFinish();
								pCUpdateT123Dlg->m_UpdateFileStatus = Update_Frame_Finsh_Wait;
								break;

			case Update_Frame_Finsh_Wait:
								if (T123_Frame_Finsh_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_CheckSum;
								}
								break;

			case Update_CheckSum:
								pCUpdateT123Dlg->PrintUpdateCheckSum();
								pCUpdateT123Dlg->m_UpdateFileStatus = Update_CheckSum_Wait;
								CstrStatus = "CheckSum...";
								break;

			case Update_CheckSum_Wait:
								if (Update_CheckSum_OK == pCUpdateT123Dlg->m_RecT123UpdateStatus)
								{
									pCUpdateT123Dlg->m_UpdateFileStatus = Update_Free;
									CstrStatus = "Finish";
									pCUpdateT123Dlg->MessageBox(__T("升级完成"));
								}
								break;

			case Update_Free:	
								break;

		}

		if (TmpUpdateFileStatus != pCUpdateT123Dlg->m_UpdateFileStatus)
		{
			TmpUpdateFileStatus = pCUpdateT123Dlg->m_UpdateFileStatus;
			pCUpdateT123Dlg->SetDlgItemText(IDC_BUTTON2,CstrStatus);
		}

		if ((GetTickCount() - pCUpdateT123Dlg->m_UpdateT123Time) / 1000)
		{
			pCUpdateT123Dlg->m_UpdateT123Time = GetTickCount();
			memset(wMin,'\0',sizeof(wMin));
			memset(wSec,'\0',sizeof(wSec));

			_itow(TmpUpdateT123Time / 60,wMin,10);
			_itow(TmpUpdateT123Time % 60,wSec,10);

			cTime = wMin;
			cTime += " : ";
			cTime += wSec;

			pCUpdateT123Dlg->SetDlgItemText(IDC_EDIT5,cTime);
			TmpUpdateT123Time++;
		}
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**函数名称:		OnBnClickedButtonProgram
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::OnBnClickedButtonProgram()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwThreadID;
	CString msg;
	int Comboindex;

	DWORD   flash_res_addr = 0x00;
	DWORD   ReadAddr;

	unsigned long file_addr;
	unsigned int size;
	DWORD i;
	unsigned long j;
	unsigned char RomData[4096] = {0};
	wchar_t chAddr[20]= {'0','X'};
	m_UpdateFlag = 0;
	m_TextAddr = 0;
	m_TextSize = 0;
	m_UdataAddr = 0;
	m_UdataSize = 0;
	m_ResAddr = 0;
	m_ResSize = 0;
	m_TextCrc = 0;

	if(!OpenUartCom())
	{
		msg = "OpenUartCom Fail ";	
		MessageBox(msg);	
		return;
	}

	m_bKillMainProcThread = FALSE;
	m_UpdateFileStatus = Update_None;
	m_hMainThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
								0,
								(LPTHREAD_START_ROUTINE)ThreadMainUpdateFileProc,
								this,
								0,
								&dwThreadID
								);
	if (NULL == m_hMainThread)
	{
		msg = "CreateThread ThreadMainBtProc Fail ";	
		MessageBox(msg);	
	}

	m_hMainEvent = CreateEvent(NULL,FALSE,TRUE,NULL);

	m_ComboBoxUpdateType.EnableWindow(FALSE);

	Comboindex = m_ComboBoxUpdateType.GetCurSel();
	m_UpdateT123Type = Comboindex + 1;
	
	if (m_UpdateT123Type > 3)
	{
		MessageBox(__T("UpdateT123Type Is Too Big"));
	}

	ReadAddr = 0x100 + t123_dfu_offset;

	if (m_UpdateFileLength < ReadAddr + 4 * 7)
	{
		MessageBox(__T("m_UpdateFileLength is too short..."));
		return;
	}

	ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_UpdateFlag,4);
	ReadAddr += 4;
	if((0x1a1a1010 == m_UpdateFlag) && (m_UpdateT123Type <= Update_ALL))
	{

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_TextAddr,4);
		ReadAddr += 4;

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_TextSize,4);
		ReadAddr += 4;

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_UdataAddr,4);
		ReadAddr += 4;

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_UdataSize,4);
		ReadAddr += 4;

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_ResAddr,4);
		ReadAddr += 4;

		ByteOrderSwap((unsigned char *)(&m_pUpdateFileBuf[ReadAddr]),(unsigned char *)&m_ResSize,4);
		ReadAddr += 4;

		m_ProgType = m_UpdateT123Type;

		if(Update_Code == m_UpdateT123Type)
		{
			for(i = m_TextAddr; i < (m_TextSize+(16384)); i++)
			{
				m_TextCrc += m_pUpdateFileBuf[i];
			}
		}

		if(m_ProgType == Update_Code)
		{
			m_crcWrite 	= m_TextCrc;
			m_tmpAddr 	= m_TextAddr;
			m_fSize 	= m_TextSize;
			m_progAddr 	= m_TextAddr;
			m_crcmethod	= 0; // eatch byte sum
		}
		else if(m_ProgType == Update_Resource)
		{
			m_tmpAddr 	= m_ResAddr;
			m_fSize 	= m_ResSize;
			m_progAddr 	= m_ResAddr;
			m_crcmethod	= 1;
		}
		else if(m_ProgType == Update_ALL)
		{
			m_tmpAddr 	= 0x00;//m_TextAddr;
			m_fSize 	= m_TextAddr+m_TextSize+m_UdataSize+m_ResSize;
			m_progAddr 	= 0x00;
			m_crcmethod	= 1;
		}
		
		if(Update_Code != m_UpdateT123Type)
		{
			size = m_fSize / 4096;
			m_tmpAddr = m_progAddr;
			file_addr = m_progAddr;
			m_crcWrite = 0; 
			for(i = 0;i < size;i++)
			{
				memset(RomData,0x00,4096);
				memcpy(RomData,&m_pUpdateFileBuf[file_addr],4096);
				for(j=0;j < 4096;j += 1024)
				{
					m_crcWrite += RomData[j];
					m_crcWrite += RomData[j+1023];
				}	
				file_addr += 4096;
			}

			if(m_fSize % 4096)//last <4k data 
			{
				memset(RomData,0x00,4096);
				memcpy(RomData,&m_pUpdateFileBuf[file_addr],m_fSize % 4096);

				for(j = 1023;j < (m_fSize % 4096);j += 1024)
				{
					m_crcWrite += RomData[j];
					m_crcWrite += RomData[j - 1023];
				}
			}
		}
	}

	BOOL bRes = m_DebugFile.Open(__T("debug.txt"),CFile::modeReadWrite);
	if (!bRes)
	{
		MessageBox(__T("Open Fail"));
	}
	m_DebugFile.Flush();
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	_itow(m_progAddr,&chAddr[2],16);
	SetDlgItemText(IDC_EDIT3,chAddr);

	_itow(m_fSize,&chAddr[0],10);
	SetDlgItemText(IDC_EDIT2,chAddr);


	m_RecT123UpdateStatus = T123_None;
	m_UpdateFileStatus = Update_Init;
	m_UpdataFrameCount = 0;
	m_FrameStatus = 0;

	m_ProgressCtrlUpdate.SetRange32(0,m_fSize);

	m_UpdateT123Time = GetTickCount();
	SetDlgItemText(IDC_EDIT5,__T("0 : 0"));
	SetEvent(m_hMainEvent);
}
