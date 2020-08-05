#if !defined(AFX_GROUP_FIND_H__E7B275C1_61C3_4609_B6D9_DFA955118A1B__INCLUDED_)
#define AFX_GROUP_FIND_H__E7B275C1_61C3_4609_B6D9_DFA955118A1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Group_find.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Group_find dialog

class Group_find : public CDialog
{
// Construction
public:
	Group_find(CWnd* pParent = NULL);   // standard constructor
	CButton* btn_group_find;
	CEdit* group_number;
// Dialog Data
	//{{AFX_DATA(Group_find)
//	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Group_find)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Group_find)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUP_FIND_H__E7B275C1_61C3_4609_B6D9_DFA955118A1B__INCLUDED_)
