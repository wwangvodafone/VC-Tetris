// Tetris.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CTetrisApp:
// このクラスの実装については、Tetris.cpp を参照してください。
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CTetrisApp theApp;
