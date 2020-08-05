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
	//������ӷ�������ť
	CButton* btn_connect;
	//���뱾��IP��ַ
	CEdit* client_ip;
	//�������ӵķ������˿ں�
	CEdit* client_iport;
	//�����û���
	CEdit* client_name;
	//�����û�����
	CEdit* client_key;
	//���ע���û���ť
	CButton* btn_register;
	//�����¼��ť
	CButton* btn_login;
	//����˳���¼��ť
	CButton* btn_exit;
	//�������Ⱥ�İ�ť
	CButton* btn_group_create;
	//����Ĵ�����Ⱥ������
	CEdit* group_name_create;
	//�������Ⱥ�İ�ť
	CButton* btn_group_find;
	//����Ĵ�����Ⱥ������
	CEdit* group_name_find;
	//���������Ӻ��Ѱ�ť
	CButton* btn_friend_find;
	//����������Ӻ��Ѱ�ť
	CEdit* friend_find;
	//���ɾ�����Ѱ�ť
	CButton* btn_friend_delete;
	//����ɾ������
	CEdit* friend_delete;

	//�����ʼȺ�İ�ť
	CButton* btn_group_chat;
	//�����ʼ����˽�İ�ť
	CButton* btn_friend_chat;
	//�����Ҫ��ʼ����ĺ�������
	CEdit* friend_chat_edit;

	//��ʾ��Ⱥ���б�
	CEdit* group_list;
	//��ʾ�ĺ����б�
	CEdit* friend_list;
	//�����Ҫ��ʼ�����Ⱥ������
	CEdit* group_chat_edit;

	//ȫ�ֵĶ˿ںű���
	SOCKET SClient;
	//��ʾ����������
	CEdit* model;
	//��ʾ�������Ⱥ������
	CEdit* group_name;
	//��ʾ����������
	CEdit* chat_val;
	//�������������
	CEdit* send_val;
	//���������Ϣ��ť
	CButton* btn_send;
	//����˳�Ⱥ��
	CButton* btn_group_exit;
	//����Ҫ�˳���Ⱥ������
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
