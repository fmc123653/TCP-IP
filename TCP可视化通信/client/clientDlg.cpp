// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
//定义库函数
#include "group_chat.h"
#include "Group_find.h"
#include "friend_find.h"
#include "group.h"

#include<Winsock2.h>
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
#define DATA_BUFFER 1024
#pragma comment(lib, "ws2_32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
DWORD WINAPI recv_msg(LPVOID lpParamter); 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	//每个控件对应赋值
	client_ip = (CEdit *)GetDlgItem(IDC_EDIT1);
	client_iport = (CEdit *)GetDlgItem(IDC_EDIT2);
	btn_connect = (CButton *)GetDlgItem(IDC_BUTTON1);
	client_name=(CEdit *)GetDlgItem(IDC_EDIT3);
	client_key=(CEdit *)GetDlgItem(IDC_EDIT4);
	btn_register=(CButton *)GetDlgItem(IDC_BUTTON2);
	btn_login=(CButton *)GetDlgItem(IDC_BUTTON3);
	btn_exit=(CButton *)GetDlgItem(IDC_BUTTON4);

	btn_group_create=(CButton *)GetDlgItem(IDC_BUTTON5);
	btn_group_find=(CButton *)GetDlgItem(IDC_BUTTON6);
	btn_friend_find=(CButton *)GetDlgItem(IDC_BUTTON7);
	btn_group_chat=(CButton *)GetDlgItem(IDC_BUTTON9);
	btn_friend_chat=(CButton *)GetDlgItem(IDC_BUTTON10);
	
	group_list= (CEdit *)GetDlgItem(IDC_EDIT5);
	friend_list= (CEdit *)GetDlgItem(IDC_EDIT6);
	group_chat_edit= (CEdit *)GetDlgItem(IDC_EDIT7);
	friend_chat_edit= (CEdit *)GetDlgItem(IDC_EDIT8);

	model=(CEdit *)GetDlgItem(IDC_EDIT9);
	chat_val=(CEdit *)GetDlgItem(IDC_EDIT10);
	send_val=(CEdit *)GetDlgItem(IDC_EDIT11);
	group_name=(CEdit *)GetDlgItem(IDC_EDIT12);
	btn_send=(CButton *)GetDlgItem(IDC_BUTTON8);

	group_name_create=(CEdit *)GetDlgItem(IDC_EDIT16);
	group_name_find=(CEdit *)GetDlgItem(IDC_EDIT13);

	btn_group_exit=(CButton *)GetDlgItem(IDC_BUTTON6);
	group_name_exit=(CEdit *)GetDlgItem(IDC_EDIT14);

	btn_friend_find=(CButton *)GetDlgItem(IDC_BUTTON7);
	friend_find=(CEdit *)GetDlgItem(IDC_EDIT15);
	btn_friend_delete=(CButton *)GetDlgItem(IDC_BUTTON12);
	friend_delete=(CEdit *)GetDlgItem(IDC_EDIT17);

	CDialog::OnInitDialog();
	//先锁死除ip地址和端口号的一切其他窗口按钮,等连接成功再解锁
	client_name->SetReadOnly(TRUE);
	client_key->SetReadOnly(TRUE);
	btn_register->EnableWindow(FALSE);
	btn_login->EnableWindow(FALSE);
	btn_exit->EnableWindow(FALSE);

	btn_group_create->EnableWindow(FALSE);
	btn_group_find->EnableWindow(FALSE);
	btn_friend_find->EnableWindow(FALSE);
	btn_group_chat->EnableWindow(FALSE);
	btn_friend_chat->EnableWindow(FALSE);
	group_list->SetReadOnly(TRUE);
	friend_list->SetReadOnly(TRUE);
	group_chat_edit->SetReadOnly(TRUE);
	friend_chat_edit->SetReadOnly(TRUE);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int CString_to_int(CString s)
{
	int ans=0;
	int i;
	for(i=0;i<s.GetLength();i++)
	{
		ans*=10;
		ans+=(s[i]-'0');
	}
	return ans;
}
CString int_to_CString(int data)
{
	CString s;
	stack<int>q;
	while(data>0)
	{
		q.push(data%10);
		data/=10;
	}
	while(!q.empty())
	{
		s+=(q.top()+'0');
		q.pop();
	}
	return s;
}
//定义全局的客户端流式套接口
SOCKET sClient;
void CClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	CString ip;
	client_ip->GetWindowText(ip);
	CString Iport;
	client_iport->GetWindowText(Iport);
	if(Iport=="" || ip=="")
	{
		MessageBox("请正确输入ip地址和端口号");
		return;
	}
	int iport =CString_to_int(Iport);
	WSADATA wsaData;
	
	//服务器端地址
	struct sockaddr_in ser;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		MessageBox("Failed to load Winsock");
		return;
	}
	//填写要连接的服务器地址信息
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iport);
	//inet_addr( )函数将命令行的点分 IP 地址转化为用二进制表示的网络字节顺序的 IP 地址
	ser.sin_addr.s_addr=inet_addr(ip);
	//建立客户端流式套接口
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if(sClient==INVALID_SOCKET)
	{
		MessageBox("socket( ) Failed");
		return;
	}
	//赋值
	SClient=sClient;
	//请求与服务器端建立 TCP 连接
	if(connect(sClient,(struct sockaddr*)&ser,sizeof(ser))==INVALID_SOCKET)
	{
		MessageBox("connect( ) Failed");
		return;
	}
	else
	{
		MessageBox("连接成功");
		//锁死输入的ip地址文本框内容
		client_ip->SetReadOnly(TRUE);
		//锁死输入的端口号文本框内容
		client_iport->SetReadOnly(TRUE);
		//解锁把true改成false
		//锁死按钮
		btn_connect->EnableWindow(FALSE);

		//把注册登录相关解锁
		client_name->SetReadOnly(FALSE);
		client_key->SetReadOnly(FALSE);
		btn_register->EnableWindow(TRUE);
		btn_login->EnableWindow(TRUE);
	//	btn_exit->EnableWindow(TRUE);
	}
//	int 
//	MessageBox(iport);
}
//注册按钮
void CClientDlg::OnButton2() 
{

	// TODO: Add your control notification handler code here
	CString CSname,CSkey;
	//进行登录名和密码的赋值
	client_name->GetWindowText(CSname);
	client_key->GetWindowText(CSkey);
	if(CSname=="" || CSkey=="")
	{
		MessageBox("请正确输入注册姓名和注册密码");
		return;
	}
	char buf[200],name[20],key[20];
	memset(buf,0,sizeof(buf));
	memset(name,0,sizeof(name));
	memset(key,0,sizeof(key));
	int i;
	for(i=0;i<CSname.GetLength();i++)
		name[i]=CSname[i];
	for(i=0;i<CSkey.GetLength();i++)
		key[i]=CSkey[i];
	strcat(buf,"1 ");
	strcat(buf,name);
	strcat(buf," ");
	strcat(buf,key);

	send(sClient,buf,sizeof(buf),0);
	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	CString result="";
	for(i=0;i<strlen(buf);i++)
		result+=buf[i];
	MessageBox("服务器反馈结果："+result);
	if(result!="注册成功")return;
}
//专门用来显示群组列表信息的函数
void Print_group_list(char *buf)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CString result;
	int i;
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
	//显示
	dlg->group_list->SetWindowText(result);
}
//打印好友列表信息
void Print_friend_list(char *buf)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CString	result;
	int i;
	for(i=0;i<strlen(buf);i++)
	{
		result+=buf[i];
	}
	dlg->friend_list->SetWindowText(result);
}
//打印服务器反馈结果信息
void Print_Message(char *buf)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CString result;
	int i;
	for(i=0;i<strlen(buf);i++)
		result+=buf[i];
	dlg->MessageBox("服务器反馈结果："+result);
}
CString Print_time()
{
	CTime tim = CTime::GetCurrentTime(); ///构造CTime对象 
	CString Tim = tim.Format("%Y-%m-%d %H:%M:%S");  
	return Tim;
}
//打印其他人说话的内容
void Print_other_client(char *buf,char Model)
{
	CString CSgroup_name;
	CString CSval;
	CString CSclient_name_other;
	CString CSclient_name;
	int i;
	for(i=0;i<strlen(buf);i++)
	{
		if(buf[i]==' ')break;
		CSgroup_name+=buf[i];
	}
	i++;
	for(;i<strlen(buf);i++)
	{
		if(buf[i]==' ')break;
		CSval+=buf[i];
	}
	i++;
	for(;i<strlen(buf);i++)
	{
		CSclient_name+=buf[i];
	}
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	if(Model=='4')
	{
		CString CSgroup_name2;
		
		dlg->group_name->GetWindowText(CSgroup_name2);
		//说明当前该用户没有在用这个群聊天，所以不显示
		if(CSgroup_name!=CSgroup_name2)
			return;
	}
	else if(Model=='7')
	{
		CString CSclient_name;
		dlg->client_name->GetWindowText(CSclient_name);
		//说明当前私聊的聊天对象不是你
		if(CSgroup_name!=CSclient_name)
			return;
	}
	//显示聊天内容
	dlg->chat_val->ReplaceSel("["+CSclient_name+"] "+Print_time()+"\r\n "+CSval+"\r\n\r\n");
}
//打印自己说的话
void Print_own_client(CString client_name,CString val)
{
	int d=53;
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	int i;
	CString s=Print_time()+" ["+client_name+"]";
	CString s1="";
	for(i=0;i<int(d-s.GetLength());i++)
	{
		s1+=" ";
	}
	s1+=s;
	CString s2="";
	for(i=0;i<int(d-val.GetLength())-1;i++)
	{
		s2+=" ";
	}
	s2+=val;
	dlg->chat_val->ReplaceSel(s1+"\r\n"+s2+"\r\n\r\n");
}
void CClientDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString CSname,CSkey;
	//进行登录名和密码的赋值
	client_name->GetWindowText(CSname);
	client_key->GetWindowText(CSkey);
	if(CSname=="" || CSkey=="")
	{
		MessageBox("请正确输入登录姓名和登录密码");
		return;
	}
	char buf[2000],name[20],key[20];
	memset(buf,0,sizeof(buf));
	memset(name,0,sizeof(name));
	memset(key,0,sizeof(key));
	int i;
	for(i=0;i<CSname.GetLength();i++)
		name[i]=CSname[i];
	for(i=0;i<CSkey.GetLength();i++)
		key[i]=CSkey[i];
	//插入2让服务器判断指令
	strcat(buf,"2 ");
	strcat(buf,name);
	strcat(buf," ");
	strcat(buf,key);

	send(sClient,buf,sizeof(buf),0);
	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	CString result;
	for(i=0;i<strlen(buf);i++)
		result+=buf[i];
	MessageBox("服务器反馈结果："+result);
	
	if(strcmp(buf,"登录成功")!=0)return;


	//开启一个线程用来接收各种信息，这样就可以实现实时更新界面信息了
	HANDLE hThread = CreateThread(NULL, 0, recv_msg,(LPVOID *)&sClient, 0, NULL);
    //这里不是关闭子线程，而是等子线程函数结束时，释放占用的内存 
    CloseHandle(hThread);

	//锁死按钮
	btn_login->EnableWindow(FALSE);
	btn_register->EnableWindow(FALSE);
	//锁死文本框
	client_name->SetReadOnly(TRUE);
	client_key->SetReadOnly(TRUE);
	//解锁退出按钮
	btn_exit->EnableWindow(TRUE);
	//解锁
	btn_group_create->EnableWindow(TRUE);
	btn_group_find->EnableWindow(TRUE);
	btn_friend_find->EnableWindow(TRUE);
	btn_group_chat->EnableWindow(TRUE);
	btn_friend_chat->EnableWindow(TRUE);
	group_chat_edit->SetReadOnly(FALSE);
	friend_chat_edit->SetReadOnly(FALSE);
}
//子线程内容
DWORD WINAPI recv_msg(LPVOID lpParamter)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	//将传递过来的参数类型调整为整数型 
	SOCKET socket=*((SOCKET*)lpParamter);
	char buf[2000];
	while(true)
	{
		memset(buf,0,sizeof(buf));
		int ret=recv(sClient,buf,sizeof(buf),0);
		//表示对方无反应
		if(ret==-1)
		{
			return NULL;
		}
		//我们在这里做个标志
		//buf[0]为1，打印数组列表信息
		//buf[0]为2，打印好友列表信息
		//buf[0]为3，打印创建服务器反馈结果
		//buf[0]为4，打印通过群聊发送来的信息
		//buf[0]为5，打印通过私聊发送来的信息
		if(buf[0]=='1')
			Print_group_list(buf+2);
		else if(buf[0]=='2')
			Print_friend_list(buf+2);
		else if(buf[0]=='3')
			Print_Message(buf+2);
		else if(buf[0]=='4'||buf[0]=='7')
			Print_other_client(buf+2,buf[0]);
		/*
		if(buf[0]=='1'||buf[0]=='2')continue;
		CString val;
		int i;
		for(i=0;i<strlen(buf);i++)
			val+=buf[i];
		dlg->MessageBox(val);
		*/
	}
}
void CClientDlg::OnButton4() 
{
	send(sClient,"exit",sizeof("exit"),0);
	// TODO: Add your control notification handler code here
	//解锁输入的ip地址文本框内容
	client_ip->SetReadOnly(FALSE);
	//解锁输入的端口号文本框内容
	client_iport->SetReadOnly(FALSE);
	//解锁把true改成false
	//解锁按钮
	btn_connect->EnableWindow(TRUE);

	//把注册登录相关解死
	client_name->SetReadOnly(TRUE);
	client_key->SetReadOnly(TRUE);
	btn_register->EnableWindow(FALSE);
	btn_login->EnableWindow(FALSE);
	btn_exit->EnableWindow(FALSE);

	btn_group_create->EnableWindow(FALSE);
	btn_group_find->EnableWindow(FALSE);
	btn_friend_find->EnableWindow(FALSE);
	btn_group_chat->EnableWindow(FALSE);
	btn_friend_chat->EnableWindow(FALSE);
	group_chat_edit->SetReadOnly(TRUE);
	friend_chat_edit->SetReadOnly(TRUE);

	//清空数据
	client_name->SetWindowText("");
	client_key->SetWindowText("");
	client_ip->SetWindowText("");
	client_iport->SetWindowText("");
	group_list->SetWindowText("");
	friend_list->SetWindowText("");
	group_chat_edit->SetWindowText("");
	friend_chat_edit->SetWindowText("");
}

void CClientDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CString CSgroup_name;
	group_name_find->GetWindowText(CSgroup_name);
	char buf[200];
	memset(buf,0,sizeof(buf));
	strcat(buf,"2 ");
	int i;
	for(i=0;i<CSgroup_name.GetLength();i++)
		buf[i+2]=CSgroup_name[i];
	send(sClient,buf,sizeof(buf),0);
}

void CClientDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CString CSgroup_name;
	group_name_exit->GetWindowText(CSgroup_name);
	char buf[200];
	memset(buf,0,sizeof(buf));
	strcat(buf,"3 ");
	int i;
	for(i=0;i<CSgroup_name.GetLength();i++)
		buf[i+2]=CSgroup_name[i];
	send(sClient,buf,sizeof(buf),0);

}
//搜索添加好友
void CClientDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CString CSclient_name;
	friend_find->GetWindowText(CSclient_name);
	char buf[200];
	memset(buf,0,sizeof(buf));
	strcat(buf,"5 ");
	int i;
	for(i=0;i<CSclient_name.GetLength();i++)
		buf[i+2]=CSclient_name[i];
	send(sClient,buf,sizeof(buf),0);
}
//仅仅告诉聊天界面当前聊天模式
void CClientDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CString CSgroup_name;
	group_chat_edit->GetWindowText(CSgroup_name);
	model->SetWindowText("群聊");
	group_name->SetWindowText(CSgroup_name);
	chat_val->SetWindowText("");

}
//发送信息，交流框一栏
void CClientDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CString Model;
	model->GetWindowText(Model);
	//这里我一开始定义的时候有点儿错误了，说明一下：CSgroup_name为群聊模式时指群组名字，私聊模式为好友名字
	CString CSgroup_name;
	group_name->GetWindowText(CSgroup_name);
	CString val;
	send_val->GetWindowText(val);
	char buf[2000];
	memset(buf,0,sizeof(buf));
	if(Model=="群聊")
		strcat(buf,"4 ");
	else if(Model=="私聊")
		strcat(buf,"7 ");
	int i,j=1;
	for(i=0;i<CSgroup_name.GetLength();i++)
		buf[++j]=CSgroup_name[i];
	buf[++j]=' ';
	for(i=0;i<val.GetLength();i++)
		buf[++j]=val[i];
	CString CSclient_name;
	client_name->GetWindowText(CSclient_name);
	Print_own_client(CSclient_name,val);
	send(sClient,buf,sizeof(buf),0);
	send_val->SetWindowText("");
}
//创建群聊
void CClientDlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	char buf[200];
	memset(buf,0,sizeof(buf));
	strcat(buf,"1 ");
	CString CSgroup_name;
	group_name_create->GetWindowText(CSgroup_name);
	int i;
	for(i=0;i<CSgroup_name.GetLength();i++)
		buf[i+2]=CSgroup_name[i];
	send(sClient,buf,sizeof(buf),0);

}

void CClientDlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	CString CSclient_name;
	friend_delete->GetWindowText(CSclient_name);
	char buf[200];
	memset(buf,0,sizeof(buf));
	strcat(buf,"6 ");
	int i;
	for(i=0;i<CSclient_name.GetLength();i++)
		buf[i+2]=CSclient_name[i];
	send(sClient,buf,sizeof(buf),0);
}

void CClientDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	model->SetWindowText("私聊");
	CString CSclient_name;
	friend_chat_edit->GetWindowText(CSclient_name);
	group_name->SetWindowText(CSclient_name);
	chat_val->SetWindowText("");
}

