
// UpdateT123.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpdateT123App:
// �йش����ʵ�֣������ UpdateT123.cpp
//

class CUpdateT123App : public CWinApp
{
public:
	CUpdateT123App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUpdateT123App theApp;