
// GAME_PROJECT.h : GAME_PROJECT ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "Player.h"


// CGAME_PROJECTApp:
// �� Ŭ������ ������ ���ؼ��� GAME_PROJECT.cpp�� �����Ͻʽÿ�.
//

class CGAME_PROJECTApp : public CWinApp
{
public:
	CGAME_PROJECTApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGAME_PROJECTApp theApp;
