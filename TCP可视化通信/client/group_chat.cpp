// group_chat.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "group_chat.h"
#include "clientDlg.h"
#include<Winsock2.h>
#include<stack>
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// group_chat dialog


group_chat::group_chat(CWnd* pParent /*=NULL*/)
	: CDialog(group_chat::IDD, pParent)
{
	//{{AFX_DATA_INIT(group_chat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void group_chat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(group_chat)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(group_chat, CDialog)
	//{{AFX_MSG_MAP(group_chat)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// group_chat message handlers

BOOL group_chat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	group_name = (CEdit *)GetDlgItem(IDC_EDIT1);
	btn_group_chat = (CButton *)GetDlgItem(IDC_BUTTON1);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void group_chat::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CClientDlg* parent = (CClientDlg*)GetParent();
	SOCKET sClient=parent->SClient;
	char buf[2000];
	CString val;
	group_name->GetWindowText(val);
	int i;
	memset(buf,0,sizeof(buf));
	strcat(buf,"1 ");
	for(i=0;i<val.GetLength();i++)
		buf[i+2]=val[i];
	send(sClient,buf,sizeof(buf),0);

	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	val="";
	for(i=0;i<strlen(buf);i++)
		val+=buf[i];
	MessageBox("服务器反馈结果："+val);
	//接收列表信息
	memset(buf,0,sizeof(buf));
	CString result;
	recv(sClient,buf,sizeof(buf),0);
	result="";
	for(i=0;i<strlen(buf);i++)
	{
		if(i==0)
			result+="[";
		if(buf[i]==' ')
		{
			result+="]\r\n\r\n";
			if(i!=strlen(buf)-1)
				result+="[";
		}	
		else result+=buf[i];
	}
	parent->group_list->SetWindowText(result);
}
