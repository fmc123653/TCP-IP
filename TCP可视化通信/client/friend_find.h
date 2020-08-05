#if !defined(AFX_FRIEND_FIND_H__5911ED78_9B50_4197_BD8C_EFBFBDE50EFF__INCLUDED_)
#define AFX_FRIEND_FIND_H__5911ED78_9B50_4197_BD8C_EFBFBDE50EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// friend_find.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// friend_find dialog

class friend_find : public CDialog
{
// Construction
public:
	friend_find(CWnd* pParent = NULL);   // standard constructor
	CButton* btn_friend_chat;
	CEdit* friend_name;
// Dialog Data
	//{{AFX_DATA(friend_find)
//	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(friend_find)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(friend_find)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRIEND_FIND_H__5911ED78_9B50_4197_BD8C_EFBFBDE50EFF__INCLUDED_)
