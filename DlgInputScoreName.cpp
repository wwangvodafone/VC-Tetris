// DlgInputScoreName.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "DlgInputScoreName.h"


// CDlgInputScoreName dialog

IMPLEMENT_DYNAMIC(CDlgInputScoreName, CDialog)
CDlgInputScoreName::CDlgInputScoreName(CWnd* pParent, int gameLevel, int russScore)
	: CDialog(CDlgInputScoreName::IDD, pParent)
	, level(0)
	, score(0)
{
	level = gameLevel;
	score = russScore;
}

CDlgInputScoreName::~CDlgInputScoreName()
{
}

void CDlgInputScoreName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInputScoreName, CDialog)
END_MESSAGE_MAP()


// CDlgInputScoreName message handlers

void CDlgInputScoreName::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	HKEY hkResult;
	DWORD dwDisposition;	// ˆ—Œ‹‰Ê‚ðŽó‚¯Žæ‚é

	CString KeyName = "SOFTWARE\\RussGame";  

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyName, 0, KEY_WRITE, &hkResult) != ERROR_SUCCESS) { //no register

		if (::RegCreateKeyEx(HKEY_LOCAL_MACHINE, KeyName, 0, "", REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS, NULL, &hkResult, &dwDisposition) != ERROR_SUCCESS) {
			return; //¶¬‚ÉŽ¸”s
		}

	}

	CString userName;
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(userName);

	long ret2 = ::RegSetValueEx(hkResult, "GameUser", NULL, REG_SZ, (CONST BYTE*)(LPCTSTR)userName, userName.GetLength() + 1);
	DWORD dw = score;  
	::RegSetValueEx(hkResult, "GameScore", NULL, REG_DWORD, (CONST BYTE*)&dw, sizeof(dw)); 
	dw = level;
	::RegSetValueEx(hkResult, "GameLevel", NULL, REG_DWORD, (CONST BYTE*)&dw, sizeof(dw));

	::RegCloseKey(hkResult);
	CDialog::OnOK();
}
