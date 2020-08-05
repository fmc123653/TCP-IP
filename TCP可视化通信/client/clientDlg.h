// clientDlg.h : header file
//
#include<Winsock2.h>
#if !defined(AFX_CLIENTDLG_H__002C2FEB_7A34_41BD_8361_B219DC3C89F4__INCLUDED_)
#define AFX_CLIENTDLG_H__002C2FEB_7A34_41BD_8361_B219DC3C89F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
//private:
	//点击连接服务器按钮
	CButton* btn_connect;
	//输入本地IP地址
	CEdit* client_ip;
	//输入连接的服务器端口号
	CEdit* client_iport;
	//输入用户名
	CEdit* client_name;
	//输入用户密码
	CEdit* client_key;
	//点击注册用户按钮
	CButton* btn_register;
	//点击登录按钮
	CButton* btn_login;
	//点击退出登录按钮
	CButton* btn_exit;
	//点击创建群聊按钮
	CButton* btn_group_create;
	//输入的创建的群聊名称
	CEdit* group_name_create;
	//点击搜索群聊按钮
	CButton* btn_group_find;
	//输入的创建的群聊名称
	CEdit* group_name_find;
	//点击搜索添加好友按钮
	CButton* btn_friend_find;
	//输入搜索添加好友按钮
	CEdit* friend_find;
	//点击删除好友按钮
	CButton* btn_friend_delete;
	//输入删除姓名
	CEdit* friend_delete;

	//点击开始群聊按钮
	CButton* btn_group_chat;
	//点击开始好友私聊按钮
	CButton* btn_friend_chat;
	//输入的要开始聊天的好友名称
	CEdit* friend_chat_edit;

	//显示的群组列表
	CEdit* group_list;
	//显示的好友列表
	CEdit* friend_list;
	//输入的要开始聊天的群聊名称
	CEdit* group_chat_edit;

	//全局的端口号变量
	SOCKET SClient;
	//显示的聊天类型
	CEdit* model;
	//显示的聊天的群聊名称
	CEdit* group_name;
	//显示的聊天内容
	CEdit* chat_val;
	//输入的聊天内容
	CEdit* send_val;
	//点击发送信息按钮
	CButton* btn_send;
	//点击退出群聊
	CButton* btn_group_exit;
	//输入要退出的群聊名称
	CEdit* group_name_exit;
// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton9();
	afx_msg void OnButton8();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__002C2FEB_7A34_41BD_8361_B219DC3C89F4__INCLUDED_)
