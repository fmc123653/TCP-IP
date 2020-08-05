// group.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "group.h"
#include "clientDlg.h"
#include <string>
#include <iostream>
#include<fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//DWORD WINAPI recv_msg(LPVOID lpParamter);
/////////////////////////////////////////////////////////////////////////////
// group dialog


group::group(CWnd* pParent /*=NULL*/)
	: CDialog(group::IDD, pParent)
{
	//{{AFX_DATA_INIT(group)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void group::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(group)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(group, CDialog)
	//{{AFX_MSG_MAP(group)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// group message handlers
char Group_number[20];
SOCKET SClient;
BOOL group::OnInitDialog() 
{
	CDialog::OnInitDialog();
	btn_send=(CButton *)GetDlgItem(IDC_BUTTON1);
	btn_group_exit=(CButton *)GetDlgItem(IDC_BUTTON2);
	group_name=(CEdit *)GetDlgItem(IDC_EDIT1);
	group_number=(CEdit *)GetDlgItem(IDC_EDIT2);
	chat_val=(CEdit *)GetDlgItem(IDC_EDIT3);
	send_val=(CEdit *)GetDlgItem(IDC_EDIT4);
	friend_list=(CEdit *)GetDlgItem(IDC_EDIT5);
	
	CClientDlg* parent = (CClientDlg*)GetParent();
	CString val;
	parent->group_chat_edit->GetWindowText(val);
	group_name->SetWindowText(val);

	CString name;
	parent->client_name->GetWindowText(name);
	char buf[2000];
	int i;
	memset(buf,0,sizeof(buf));
	strcat(buf,"4 ");
	for(i=0;i<name.GetLength();i++)
	{
		buf[i+2]=name[i];
		buf[i+3]=' ';
	}
	char Group_name[100];
	memset(Group_name,0,sizeof(Group_name));
	for(i=0;i<val.GetLength();i++)
		Group_name[i]=val[i];
	strcat(buf,Group_name);

	SClient=parent->SClient;
	send(SClient,buf,sizeof(buf),0);

	memset(buf,0,sizeof(buf));
	recv(SClient,buf,sizeof(buf),0);

	memset(Group_number,0,sizeof(Group_number));
	
	CString CGroup_number;
	CString group_client;
	for(i=0;i<int(strlen(buf));i++)
	{
		if(buf[i]==' ')break;
		CGroup_number+=buf[i];
		Group_number[i]=buf[i];
	}
	i++;
	for(;i<int(strlen(buf));i++)
	{
		group_client+=buf[i];
	}
	group_number->SetWindowText(CGroup_number);
	friend_list->SetWindowText(group_client);

	// TODO: Add extra initialization here
	
	//开启线程
//	HANDLE hThread = CreateThread(NULL, 0, recv_msg,(LPVOID *)&SClient, 0, NULL);
    //这里不是关闭子线程，而是等子线程函数结束时，释放占用的内存 
   // CloseHandle(hThread);
	AfxBeginThread(recv_msg,(LPVOID*)&SClient);  //生成线程，进行读写
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void group::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString val;
	send_val->GetWindowText(val);
	char buf[2000];
	memset(buf,0,sizeof(buf));
	int i;
	strcat(buf,"5 ");
	strcat(buf,Group_number);
	char suf[2000];
	memset(suf,0,sizeof(suf));
	for(i=0;i<val.GetLength();i++)
		suf[i]=val[i];
	strcat(buf," ");
	strcat(buf,suf);
	send(SClient,buf,sizeof(buf),0);
	chat_val->ReplaceSel(val+"\r\n");
}
void group::Print(CString s)
{
	chat_val->ReplaceSel(s);
}
UINT group::recv_msg(LPVOID lpParamter)
//DWORD WINAPI group::recv_msg(LPVOID lpParamter)
{
	//将传递过来的参数类型调整为整数型 
	SOCKET socket=*((SOCKET*)lpParamter);
	char buf[2000];
//	group *dlg =AfxGetMainWnd() ->GetActiveWindow();
//	group  *dlg;

///	group *dlg ;

//	dlg->m_hWnd->Print  ;

//	CWnd *wnd  = AfxGetMainWnd();
  //  HWND hwnd = wnd->GetSafeHwnd();

//	group* dlg= (group*)group::FromHandle(hwnd);
//	dlg->m_hWnd->Print("here");
//	Print("hehe");
//	group dlg;
//	dlg.Print("hehe");
	while(true)
	{		
		
		memset(buf,0,sizeof(buf));
		int ret=recv(socket,buf,sizeof(buf),0);
		CString val;
		int i;
		for(i=0;i<strlen(buf);i++)
		{
			val+=buf[i];
		}
		
	//	g
	//	Print(val);
	}
	return NULL;
}
