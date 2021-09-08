#pragma once


// CDlgInputScoreName dialog

class CDlgInputScoreName : public CDialog
{
	DECLARE_DYNAMIC(CDlgInputScoreName)

public:
	CDlgInputScoreName(CWnd* pParent = NULL, int gameLevel = 0, int russScore = 0);   // standard constructor
	virtual ~CDlgInputScoreName();

// Dialog Data
	enum { IDD = IDD_DIALOG_INPUTNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

private:
	LPBYTE CString_To_LPBYTE(CString str);

	// ゲームレベル
	int level;
	// ゲームスコア
	int score;
};
