
// P2PTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CP2PTestApp: 
// �йش����ʵ�֣������ P2PTest.cpp
//

class CP2PTestApp : public CWinApp
{
public:
	CP2PTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CP2PTestApp theApp;