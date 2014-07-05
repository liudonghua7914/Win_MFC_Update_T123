
// UpdateT123.cpp : ����Ӧ�ó��������Ϊ��
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


// CUpdateT123App ����

CUpdateT123App::CUpdateT123App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUpdateT123App ����

CUpdateT123App theApp;


// CUpdateT123App ��ʼ��

BOOL CUpdateT123App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CUpdateT123Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô�����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô�����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}




/*********************************************************************************************************************************************
**��������:		ReadConfigFile
**��������:
**��ڲ���:
**���ز���:
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
	 * ��ȡ�����ļ�
	 */
	bRes = m_FlyConfigFile.Open(__T("FlyConfig.ini"),CFile::modeRead);
	if (bRes)
	{
		FileLength  = m_FlyConfigFile.GetLength();
		pBuf = new char[FileLength + 1];
		pBuf[FileLength] = '\0';
		m_FlyConfigFile.Read(pBuf,FileLength);
	}

	/*
	 *	���������ļ�
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

				bNeedProc = FALSE;
				bNode = FALSE;
				IDlength = 0;
				ValueLength = 0;
			}
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

	delete pBuf;

	return bRes;
}

/*********************************************************************************************************************************************
**��������:		InitDCB
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
BOOL CUpdateT123Dlg::InitDCB(void)
{
	DCB PortDCB;

	GetCommState(m_hComm,&PortDCB);
	PortDCB.DCBlength = sizeof(DCB);
	PortDCB.BaudRate = m_BaudRate;
	PortDCB.ByteSize = m_ByteSize;
	PortDCB.fBinary = TRUE;		//Win32��֧�ַǶ����ƴ��д���ģʽ������ΪTRUE 
	PortDCB.fParity = FALSE;	//��żУ�� 
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
**��������:		InitCommTimeouts
**��������:
**��ڲ���:
**���ز���:
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
**��������:		ThreadCommProc
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::ReadUartCom(BYTE *p,UINT32 Len)
{
	UINT32 i;
	for (i = 0;i < Len;i++)
	{
		
	}
}
/*********************************************************************************************************************************************
**��������:		ThreadCommProc
**��������:
**��ڲ���:
**���ز���:
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
												//���ö�����
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
			//���ö�����
			pUpdateT123Dlg->ReadUartCom(pUpdateT123Dlg->m_RecBuf,dwLength);
		}
	}

	return TRUE;
}
/*********************************************************************************************************************************************
**��������:		OpenUartCom
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
void CUpdateT123Dlg::OpenUartCom(void)
{
	DWORD dwThreadID;
/*
 *	���ڳ�ʼ��
*/
	CString msg;
	if (!ReadConfigFile())
	{
		msg = "Open ReadConfigFile Fail";
		MessageBox(msg);
	}

	m_hComm = CreateFile(m_ComName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	if(INVALID_HANDLE_VALUE == m_hComm)
	{
		msg = "Open Fail ";
		msg += m_ComName;
		MessageBox(msg);
	}

	SetCommMask(m_hComm,EV_RXCHAR);
	SetupComm(m_hComm,1024,512);
	PurgeComm(m_hComm,PURGE_TXCLEAR|PURGE_RXCLEAR);

	if(!InitDCB())
	{
		msg = "InitDCB Fail ";	
		MessageBox(msg);
	}
	if (!InitCommTimeouts())
	{
		msg = "InitCommTimeouts Fail ";	
		MessageBox(msg);	
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
	}

}
