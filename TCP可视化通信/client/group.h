#if !defined(AFX_GROUP_H__B222BB92_621D_4DBE_9986_CEE4278FF595__INCLUDED_)
#define AFX_GROUP_H__B222BB92_621D_4DBE_9986_CEE4278FF595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// group.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// group dialog

class group : public CDialog
{
// Construction
public:
	group(CWnd* pParent = NULL);   // standard constructor
	CButton* btn_send;
	CButton* btn_group_exit;
	CEdit* group_name;
	CEdit* group_number;
	CEdit* chat_val;
	CEdit* send_val;
	CEdit* friend_list;
	void Print(CString s);
//	DWORD WINAPI recv_msg(LPVOID lpParamter);
	static UINT recv_msg(LPVOID lparam);

// Dialog Data
	//{{AFX_DATA(group)
//	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(group)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(group)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUP_H__B222BB92_621D_4DBE_9986_CEE4278FF595__INCLUDED_)
