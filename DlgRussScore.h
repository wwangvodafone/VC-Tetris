#pragma once


// CDlgRussScore dialog

class CDlgRussScore : public CDialog
{
	DECLARE_DYNAMIC(CDlgRussScore)

public:
	CDlgRussScore(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRussScore();

// Dialog Data
	enum { IDD = IDD_DIALOG_HIGHSCORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClrscore();
	virtual BOOL OnInitDialog();

private:
	BOOL GetValueFromRegister(CString& name, DWORD& score, DWORD& level);

public:
	afx_msg void OnBnClickedOk();
private:
	bool bCancelFlag;
	CStatic m_regScore;
};
