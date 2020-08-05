// friend_find.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "friend_find.h"
#include "clientDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// friend_find dialog


friend_find::friend_find(CWnd* pParent /*=NULL*/)
	: CDialog(friend_find::IDD, pParent)
{
	//{{AFX_DATA_INIT(friend_find)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void friend_find::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(friend_find)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(friend_find, CDialog)
	//{{AFX_MSG_MAP(friend_find)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL friend_find::OnInitDialog() 
{
	CDialog::OnInitDialog();
	friend_name = (CEdit *)GetDlgItem(IDC_EDIT1);
	btn_friend_chat = (CButton *)GetDlgItem(IDC_BUTTON1);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// friend_find message handlers

void friend_find::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CClientDlg* parent = (CClientDlg*)GetParent();
	SOCKET sClient=parent->SClient;
	char buf[2000];
	CString val;
	friend_name->GetWindowText(val);
	int i;
	memset(buf,0,sizeof(buf));
	//指令3表示搜索好友
	strcat(buf,"3 ");
	for(i=0;i<val.GetLength();i++)
		buf[i+2]=val[i];
	send(sClient,buf,sizeof(buf),0);

	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	val="";
	for(i=0;i<int(strlen(buf));i++)
		val+=buf[i];
	MessageBox("服务器反馈结果："+val);
	//接收好友列表
	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	CString result;
	result="";
	for(i=0;i<int(strlen(buf));i++)
	{
		result+=buf[i];
	}
	parent->friend_list->SetWindowText(result);

}

