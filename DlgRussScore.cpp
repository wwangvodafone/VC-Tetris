// DlgRussScore.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "DlgRussScore.h"


// CDlgRussScore dialog

IMPLEMENT_DYNAMIC(CDlgRussScore, CDialog)
CDlgRussScore::CDlgRussScore(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRussScore::IDD, pParent)
	, bCancelFlag(false)
{
}

CDlgRussScore::~CDlgRussScore()
{
}

void CDlgRussScore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_regScore);
}


BEGIN_MESSAGE_MAP(CDlgRussScore, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLRSCORE, OnBnClickedBtnClrscore)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRussScore message handlers

void CDlgRussScore::OnBnClickedBtnClrscore()
{
	// TODO: Add your control notification handler code here
	this->GetDlgItem(IDC_STATIC_SCORE)->SetWindowText("0");
	this->GetDlgItem(IDC_STATIC_LEVEL)->SetWindowText("0");
	this->GetDlgItem(IDC_STATIC_NAME)->SetWindowText("なし");
}

BOOL CDlgRussScore::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString regName;
	DWORD regScore, regLevel;
	GetValueFromRegister(regName, regScore, regLevel);

	CString regS;
	regS.Format("%d", regScore);
//	this->GetDlgItem(IDC_STATIC_SCORE);//
	m_regScore.SetWindowText(regS);
	regS.Format("%d", regLevel);
	this->GetDlgItem(IDC_STATIC_LEVEL)->SetWindowText(regS);
	this->GetDlgItem(IDC_STATIC_NAME)->SetWindowText(regName);

	// TODO:  Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// レジストリからレベルとスコアを取得
BOOL CDlgRussScore::GetValueFromRegister(CString& name, DWORD& score, DWORD& level)
{
	DWORD regScore;
	DWORD regLevel;
	HKEY hkResult;
	DWORD dwType;		// 値の種類を受け取る
	DWORD dwSize;		// データのサイズを受け取る
	CString KeyName = "Software\\RussGame";  

	if(	::RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyName, 0, KEY_READ, &hkResult) != ERROR_SUCCESS) {
		score = 0;
		level = 0;
		name = "なし";
		return TRUE;
	}

	::RegQueryValueEx(hkResult, "GameUser", NULL, &dwType, NULL, &dwSize);
	::RegQueryValueEx(hkResult, "GameUser", NULL, &dwType, (LPBYTE)(LPCTSTR)name, &dwSize);

	::RegQueryValueEx(hkResult, "GameScore", NULL, &dwType, NULL, &dwSize);
	::RegQueryValueEx(hkResult, "GameScore", NULL, &dwType, (LPBYTE)&regScore, &dwSize);
	::RegQueryValueEx(hkResult, "GameLevel", NULL, &dwType, NULL, &dwSize);
	::RegQueryValueEx(hkResult, "GameLevel", NULL, &dwType, (LPBYTE)&regLevel, &dwSize);
	
	::RegCloseKey(hkResult);

	score = regScore;
	level = regLevel;

	return TRUE;
}
void CDlgRussScore::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	DWORD score = 0;
	DWORD level = 0;
	CString KeyName = "Software\\RussGame";  
	HKEY hkResult;

	if(	::RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyName, 0, KEY_WRITE, &hkResult) == ERROR_SUCCESS) {

		CString userName, userScore, userLevel;
		this->GetDlgItem(IDC_STATIC_NAME)->GetWindowText(userName);
		this->GetDlgItem(IDC_STATIC_LEVEL)->GetWindowText(userLevel);
		this->GetDlgItem(IDC_STATIC_SCORE)->GetWindowText(userScore);
		
		if (userLevel == "0" && userScore == "0") {
			score = 0;
			level = 0;
			::RegSetValueEx(hkResult, "GameUser", NULL, REG_SZ, (CONST BYTE*)(LPCTSTR)userName, userName.GetLength() + 1);
			DWORD dw = score;  
			::RegSetValueEx(hkResult, "GameScore", NULL, REG_DWORD, (CONST BYTE*)&dw, sizeof(dw)); 
			dw = level;
			::RegSetValueEx(hkResult, "GameLevel", NULL, REG_DWORD, (CONST BYTE*)&dw, sizeof(dw));
		}


		::RegCloseKey(hkResult);
	}

	OnOK();
}