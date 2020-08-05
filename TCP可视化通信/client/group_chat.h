#if !defined(AFX_GROUP_CHAT_H__12C23744_D9F8_4691_BE09_FAFE4946036D__INCLUDED_)
#define AFX_GROUP_CHAT_H__12C23744_D9F8_4691_BE09_FAFE4946036D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// group_chat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// group_chat dialog

class group_chat : public CDialog
{
// Construction
public:
	group_chat(CWnd* pParent = NULL);   // standard constructor
	CButton* btn_group_chat;
	CEdit* group_name;
// Dialog Data
	//{{AFX_DATA(group_chat)
//	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(group_chat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(group_chat)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUP_CHAT_H__12C23744_D9F8_4691_BE09_FAFE4946036D__INCLUDED_)
