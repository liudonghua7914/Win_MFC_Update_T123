
// UpdateT123.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "UpdateT123.h"
#include "UpdateT123Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateT123App

BEGIN_MESSAGE_MAP(CUpdateT123App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpdateT123App 构造

CUpdateT123App::CUpdateT123App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CUpdateT123App 对象

CUpdateT123App theApp;


// CUpdateT123App 初始化

BOOL CUpdateT123App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CUpdateT123Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}




/*********************************************************************************************************************************************
**函数名称:		ReadConfigFile
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
BOOL CUpdateT123Dlg::ReadConfigFile(void)
{
	BOOL bRes = FALSE;
	char *pBuf = NULL;
	UINT FileLength = 0;

	UINT32 i = 0;
	BOOL bNode = FALSE;
	BOOL bNeedProc = FALSE;
	BOOL bID = TRUE;

	char ID[256];
	char Value[256];

	BYTE IDlength = 0;
	BYTE ValueLength = 0;


	BOOL bRunFunc = FALSE;
	/*
	 * 读取配置文件
	 */
	bRes = m_FlyConfigFile.Open(__T("FlyConfig.ini"),CFile::modeRead);
	if (bRes)
	{
		FileLength  = m_FlyConfigFile.GetLength();
		pBuf = new char[FileLength + 1];
		pBuf[FileLength] = '\0';
		m_FlyConfigFile.Read(pBuf,FileLength);
	}
	else
	{
		return FALSE;
	}

	/*
	 *	解析配置文件
	*/
	if (bRes)
	{
		for (i = 0;i <= FileLength;i++)
		{
			if ('[' == pBuf[i])
			{
				bNode = TRUE;
			}
			else if (']' == pBuf[i])
			{
				bNode = TRUE;
				bNeedProc = TRUE;
			}
			else if (('\r'== pBuf[i]) || ('\n' == pBuf[i]))
			{
				bNeedProc = TRUE;
				bID = TRUE;
			}
			else if ('=' == pBuf[i])
			{
				bID = FALSE;
			}
			else if( pBuf[i] > ' ')
			{
				if (bID)
				{
					ID[IDlength++] = pBuf[i];
					ID[IDlength] = '\0';
				}
				else
				{
					Value[ValueLength++] = pBuf[i];
					Value[ValueLength] = '\0';
				}

			}

			if (bNeedProc)
			{
				if (bNode)
				{
					if (IDlength)
					{
						//FlyConfigProcInIData(TRUE,ID,NULL);
						bRunFunc = TRUE;
					}

				}
				else
				{
					if (IDlength && ValueLength)
					{
						//FlyConfigProcInIData(FALSE,ID,Value);
						bRunFunc = TRUE;
					}	
				}

				if(bRunFunc)
				{
					bRunFunc = FALSE;

					if (bNode)
					{
						if(!memcmp("COM",ID,sizeof("COM")))
						{
							m_FlyConfigNode = Node_COM;
						}
					}
					else
					{
						if (Node_COM == m_FlyConfigNode)
						{
							if (!memcmp(("ComName"),ID,sizeof("ComName")))
							{
								m_ComName = Value;
							}
							else if (!memcmp(("BaudRate"),ID,sizeof("BaudRate")))
							{
								m_BaudRate = atoi(Value);
							}
							else if (!memcmp(("Parity"),ID,sizeof("Parity")))
							{
								if (!memcmp(("NOPARITY"),Value,sizeof("NOPARITY")))
								{
									m_Parity = NOPARITY;
								}
							}
							else if (!memcmp(("StopBits"),ID,sizeof("StopBits")))
							{
								if (!memcmp(("ONESTOPBIT"),Value,sizeof("ONESTOPBIT")))
								{
									m_StopBits = ONESTOPBIT;
								}
							}
							else if (!memcmp(("ByteSize"),ID,sizeof("ByteSize")))
							{
								m_ByteSize = atoi(Value);
							}
						}
					}	
				}


				bNeedProc = FALSE;
				bNode = FALSE;
				IDlength = 0;
				ValueLength = 0;
			}
		}
	}

	

	delete pBuf;

	return bRes;
}

/*********************************************************************************************************************************************
**函数名称:		InitDCB
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
BOOL CUpdateT123Dlg::InitDCB(void)
{
	DCB PortDCB;

	GetCommState(m_hComm,&PortDCB);
	PortDCB.DCBlength = sizeof(DCB);
	PortDCB.BaudRate = m_BaudRate;
	PortDCB.ByteSize = m_ByteSize;
	PortDCB.fBinary = TRUE;		//Win32不支持非二进制串行传输模式，必须为TRUE 
	PortDCB.fParity = FALSE;	//奇偶校验 
	PortDCB.fOutxCtsFlow = FALSE;
	PortDCB.fOutxDsrFlow = FALSE;
	PortDCB.fTXContinueOnXoff = FALSE;
	PortDCB.fOutX = FALSE;
	PortDCB.fInX = FALSE;
	PortDCB.fErrorChar = FALSE;
	PortDCB.fNull = FALSE;
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE;
	PortDCB.fAbortOnError = FALSE;
	PortDCB.Parity = m_Parity;
	PortDCB.StopBits =m_StopBits;
	if(!SetCommState(m_hComm,&PortDCB))
	{	
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**函数名称:		InitCommTimeouts
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
BOOL CUpdateT123Dlg::InitCommTimeouts(void)
{
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts(m_hComm,&CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(m_hComm,&CommTimeOuts))
	{
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**函数名称:		ReadUartCom
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::ReadUartCom(BYTE *p,UINT32 Len)
{
	UINT32 i;
	if(Len)
	{
		for (i = 0;i < Len;i++)
		{
			OnRecData(p[i]);
		}
	}
}
/*********************************************************************************************************************************************
**函数名称:		WriteUartCom
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::WriteUartCom(BYTE *p,UINT32 Len)
{
	DWORD dwLength;
	BOOL fWriteStatus;
	DWORD dwRes;
	memset(&m_ovWrite,0,sizeof(m_ovWrite));
	m_ovWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	fWriteStatus = WriteFile(m_hComm,p,Len,&dwLength,&m_ovWrite);
	if (!fWriteStatus)
	{
		if(ERROR_IO_PENDING == GetLastError())
		{
			dwRes = WaitForSingleObject(m_ovWrite.hEvent,INFINITE);
			switch(dwRes)
			{
				case WAIT_OBJECT_0:		if(GetOverlappedResult(m_hComm,&m_ovWrite,&dwLength,FALSE))
										{

										}
										break;

				case WAIT_TIMEOUT:		
					break;

				default:				
					break; 
			}	
		}
	}	
}
/*********************************************************************************************************************************************
**函数名称:		ThreadCommProc
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
DWORD WINAPI CUpdateT123Dlg::ThreadCommProc(LPCVOID pContext)
{
	DWORD dwLength;
	BOOL fReadStatus;
	BOOL bWaitingOnRead = FALSE;	
	DWORD dwRes;
	CUpdateT123Dlg *pUpdateT123Dlg = (CUpdateT123Dlg *)pContext;

	memset(&pUpdateT123Dlg->m_ovRead,0,sizeof(pUpdateT123Dlg->m_ovRead));

	pUpdateT123Dlg->m_ovRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	while (!pUpdateT123Dlg->m_bKillCommThread)
	{
		fReadStatus = ReadFile(pUpdateT123Dlg->m_hComm,pUpdateT123Dlg->m_RecBuf,RECBUFSIZE,&dwLength,&pUpdateT123Dlg->m_ovRead);//
		if (!fReadStatus)
		{
			if(ERROR_IO_PENDING == GetLastError())
			{
				dwRes = WaitForSingleObject(pUpdateT123Dlg->m_ovRead.hEvent,500);
				switch(dwRes)
				{
					case WAIT_OBJECT_0:		if(GetOverlappedResult(pUpdateT123Dlg->m_hComm,&pUpdateT123Dlg->m_ovRead,&dwLength,FALSE))
											{
												//调用读函数
												pUpdateT123Dlg->ReadUartCom(pUpdateT123Dlg->m_RecBuf,dwLength);
											}
											break;

					case WAIT_TIMEOUT:		
						break;

					default:				
						break; 
				}

			}
		}
		else
		{
			//调用读函数
			pUpdateT123Dlg->ReadUartCom(pUpdateT123Dlg->m_RecBuf,dwLength);
		}
	}

	return TRUE;
}
/*********************************************************************************************************************************************
**函数名称:		OpenUartCom
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
BOOL CUpdateT123Dlg::OpenUartCom(void)
{
	DWORD dwThreadID;
/*
 *	串口初始化
*/
	CString msg;
#if 1
	if (!ReadConfigFile())
	{
		msg = "Open ReadConfigFile Fail";
		MessageBox(msg);
		return FALSE;
	}
#else
	m_ComName = "COM5:";
	m_BaudRate = 115200;
	m_Parity = NOPARITY;
	m_StopBits = ONESTOPBIT;
	m_ByteSize = 8;
#endif
	
	m_hComm = CreateFile(m_ComName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	if(INVALID_HANDLE_VALUE == m_hComm)
	{
		msg = "Open Fail ";
		msg += m_ComName;
		MessageBox(msg);
		return FALSE;
	}

	SetCommMask(m_hComm,EV_RXCHAR);
	SetupComm(m_hComm,1024,512);
	PurgeComm(m_hComm,PURGE_TXCLEAR|PURGE_RXCLEAR);

	if(!InitDCB())
	{
		msg = "InitDCB Fail ";	
		MessageBox(msg);
		return FALSE;
	}
	if (!InitCommTimeouts())
	{
		msg = "InitCommTimeouts Fail ";	
		MessageBox(msg);	
		return FALSE;
	}

	EscapeCommFunction(m_hComm,SETDTR);
	EscapeCommFunction(m_hComm,SETRTS);
	m_bKillCommThread = FALSE;
	m_hCommThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
								0,
								(LPTHREAD_START_ROUTINE)ThreadCommProc,
								this,
								0,
								&dwThreadID
								);
	if(NULL == m_hCommThread)
	{
		msg = "CreateThread ThreadCommProc Fail ";	
		MessageBox(msg);	
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**函数名称:		CloseUartCom
**函数功能:
**入口参数:
**返回参数:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::CloseUartCom(void)
{
	m_bKillCommThread = TRUE;

	if (INVALID_HANDLE_VALUE != m_hComm)
	{
		CloseHandle(m_hComm);
	}

	if (NULL != m_hCommThread)
	{
		CloseHandle(m_hCommThread);
	}

	if (NULL != m_ovRead.hEvent)
	{
		ResetEvent(m_ovRead.hEvent);
	}

	if (NULL != m_ovWrite.hEvent)
	{
		ResetEvent(m_ovWrite.hEvent);
	}
}