// serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<map>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
map<string,SOCKET>client_vis;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	//给每个控制元件赋值
	server_val = (CEdit *)GetDlgItem(IDC_EDIT1);
	server_iport = (CEdit *)GetDlgItem(IDC_EDIT2);
	btn_makesure = (CButton *)GetDlgItem(IDC_BUTTON1);
	client_vis.clear();
	////
//	server_val->ReplaceSel("等待客户端连接...\r\n");

	CDialog::OnInitDialog();

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

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint() 
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//字符串转数字
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

void CServerDlg::Print(CString s)
{
	CServerDlg * dlg = (CServerDlg *)AfxGetApp()->GetMainWnd();
	dlg->server_val->ReplaceSel(s + "\r\n\r\n");
}
//定义子线程函数
DWORD WINAPI recv_msg(LPVOID lpParamter); 
//定义子线程函数
DWORD WINAPI server_thd(LPVOID lpParamter); 
//定义客户端结构体
struct Client
{
	int iport;
	SOCKET socket;
	char ip[20];
	char name[20];
};
//定义储存客户端结构体的动态数组
vector<Client>clients;
void CServerDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString iport;
	server_iport->GetWindowText(iport);
	int iPort=CString_to_int(iport);

	HANDLE hThread = CreateThread(NULL, 0, server_thd,(LPVOID *)&iPort, 0, NULL);
    //这里不是关闭子线程，而是等子线程函数结束时，释放占用的内存 
    CloseHandle(hThread);
	//锁死输入框
	server_iport->SetReadOnly(TRUE);
	//解锁把true改成false
	//锁死按钮
	btn_makesure->EnableWindow(FALSE);
	//
	//CServerDlg * dlg = (CServerDlg *) AfxGetApp()->GetMainWnd();
	Print("已成功构建服务器，等待客户端连接....");
}
DWORD WINAPI server_thd(LPVOID lpParamter)
{
	int iPort=*((int*)lpParamter);
	WSADATA wsaData;
	SOCKET sListen,
	sAccept;
	//客户地址长度
	int iLen;
	//服务器和客户的地址
	struct sockaddr_in ser,
	cli;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
	//	MessageBox("Failed to load Winsock");
		return NULL;
	}
	//创建服务器端套接口
	sListen=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
//		MessageBox("socket( ) Failed");
		return NULL;
	}
	//以下建立服务器端地址
	ser.sin_family=AF_INET;
	//htons( )函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
	ser.sin_port=htons(iPort);
	//htonl( )函数把一个四字节主机字节顺序的数转换为网络字节顺序的数
	//使用系统指定的 IP 地址 INADDR_ANY
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
//		MessageBox("bind( ) Failed");
		return NULL;
	}
	
	//进入监听状态
	if(listen(sListen,5)==SOCKET_ERROR)
	{
	//	MessageBox("listen( ) Failed");
		return NULL;
	}
	//初始化客户地址长度参数
	iLen=sizeof(cli);
	//进入一个无限循环，等待客户的连接请求
	while(1)
	{
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		
		if(sAccept==INVALID_SOCKET)
		{
			printf("accept( ) Failed: %d\n", WSAGetLastError( ));
			break;
		}
		Client t;
		memset(t.ip,0,sizeof(t.ip));
		strcpy(t.ip,inet_ntoa(cli.sin_addr));
		t.socket=sAccept;
		t.iport=ntohs(cli.sin_port);
		
		//每得到一个客户端的连接，就得马上开启一个单独的用来接收这个客户端发送信息的子线程函数
		HANDLE hThread = CreateThread(NULL, 0, recv_msg,(LPVOID *)&t, 0, NULL);
    	//这里不是关闭子线程，而是等子线程函数结束时，释放占用的内存 
    	CloseHandle(hThread);
	}
	closesocket(sAccept);
	closesocket(sListen);
	WSACleanup( );
	return NULL;
}
//检查是否在客户数组中，如果不在就说明在进行注册或登录
bool check(int socket)
{
	int i;
	for(i=0;i<clients.size();i++)
	{
		if(clients[i].socket==socket)return true;
	}
	return false;
}
//检查账户密码
int check_client(string name,string key)
{
	fstream f;
	f.open("client_data.txt", ios::in);//打开文件，供读
	string client_name_read,key_read;
	int result=3;
	while(f >>client_name_read>> key_read)   
	if(client_name_read==name)
	{
		if(key_read==key)
		{
			result=1;
		}
		else
		{
			result=2;
		}
		break;
	}
	f.close();
	return result;
}
CString Print_time()
{
	CTime tim = CTime::GetCurrentTime(); ///构造CTime对象 
	CString Tim = tim.Format("%Y-%m-%d %H:%M:%S");  
	return Tim;
}
CString Print_ip(Client t)
{
	CString ip;
	int i;
	for(i=0;i<strlen(t.ip);i++)
		ip+=t.ip[i];
	CString iport=int_to_CString(t.iport);
	return "IP地址："+ip+" 端口号："+iport+"\r\n";
}
int check_group(string group_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//打开文件，供读
	string group_name_read,client_name_read;
	int result=1;
	while(f >> group_name_read>>client_name_read)  
	{
		if(group_name_read==group_name)
		{
			result=2;
			break;
		}
	}
	f.close();
	//1说明这个群还没创建过
	//2说明这个群已经创建过了，不能重复创建相同的群名
	return result;
}
//将群名和用户名的关系写入文件
void write_group_to_client(string group_name,string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::out | ios::app);
	f<<group_name<<" "<<client_name<<endl;
	f.close();
}
//搜索群的时候检查此人是否加入了该群
int check_group_to_client(string group_name,string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//打开文件，供读
	string group_name_read,client_name_read;
	int result=3;
	while(f >>group_name_read>>client_name_read)
	{
		if(group_name_read==group_name)
		{
			result=2;
		}
		if(group_name_read==group_name&&client_name_read==client_name)
		{
			result=1;
			break;
		}
	}
	f.close();
	//1表示在群里，2表示不在群里，3表示查找的群不存在
	return result;
}
//当用户登录成功，需要将用户对应的群组信息返回
string get_group_list(string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//打开文件，供读
	string client_name_read,group_name_read;
	string group_list; 
	while(f>>group_name_read>>client_name_read)
	{
		if(client_name_read==client_name)
		{
			group_list+=group_name_read;
			group_list+=" ";
		}
	}
	f.close();
	return group_list;
}
//当用户登录成功，需要将用户对应的好友信息返回
string get_friend_list(string client_name)
{
	fstream f;
	f.open("client_to_client.txt", ios::in);//打开文件，供读
	string client_name1,client_name2;
	string friend_list; 
	while(f>>client_name1>>client_name2)
	{
		if(client_name1==client_name)
		{
			if(client_vis[client_name2]>0)
			friend_list+="<<在线>>";
			else friend_list+="<<离线>>";
			friend_list+="[";
			friend_list+=client_name2;
			friend_list+="]\r\n";
		}
		else if(client_name2==client_name)
		{
			if(client_vis[client_name1]>0)
			friend_list+="<<在线>>";
			else friend_list+="<<离线>>";
			friend_list+="[";
			friend_list+=client_name1;
			friend_list+="]\r\n";
		}
	}
	f.close();
	return friend_list;
}

//当打开每个群，需要返回这个群的成员情况
string get_group_client(string group_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//打开文件，供读
	string group_name_read,client_name_read;
	string result="";
	while(f>>group_name_read>>client_name_read)
	{
		if(group_name_read==group_name)
		{
			if(client_vis[client_name_read]>0)
			result+="<<在线>>";
			else result+="<<离线>>";
			result+="[";
			result+=client_name_read;
			result+="]\r\n";
		}
	}
	return result;
}

//该部分用来删除群组和用户关系，先取出，再写回
struct Group_client
{
	string group_name;
	string client_name;
};
vector<Group_client> get_back_group_client()
{
	vector<Group_client>q;
	q.clear();
	fstream f;
	f.open("group_data.txt", ios::in);//打开文件，供读
	string group_name_read,client_name_read;
	while(f>>group_name_read>>client_name_read)
	{
		Group_client a;
		a.group_name=group_name_read;
		a.client_name=client_name_read;
		q.push_back(a);
	}
	f.close();
	return q;
}
void delete_group_to_client(string group_name,string client_name)
{
	vector<Group_client>q=get_back_group_client();
	fstream f;
	//这里需要改成不要追加，覆盖原来的内容实现删除
	f.open("group_data.txt", ios::out);
	int i;
	for(i=0;i<q.size();i++)
	{
		//进行删除
		if(q[i].group_name==group_name&&q[i].client_name==client_name)continue;
		f<<q[i].group_name<<" "<<q[i].client_name<<endl;
	}
	f.close();
}
//对应把信息发送给这个群的每个成员
void send_group_to_client(string group_name,string client_name,char *val)
{
	int i,j;
	char data[2000];
	char name[20];
	memset(data,0,sizeof(data));
	memset(name,0,sizeof(name));
	strcat(data,val);
	strcat(data," ");
	for(j=0;j<client_name.length();j++)
		name[j]=client_name[j];
	strcat(data,name);
	vector<Group_client>q=get_back_group_client();
	for(i=0;i<q.size();i++)
	{
		if(q[i].group_name==group_name)
		{
			//不要把信息重复发给自己
			if(q[i].client_name==client_name)continue;
			send(client_vis[q[i].client_name],data,sizeof(data),0);
		}
	}
}

//搜索添加好友时判断好友是否存在
bool check_is_client(string client_name)
{
	fstream f;
	f.open("client_data.txt", ios::in);//打开文件，供读
	string client_name_read,client_key_read;
	bool flag=0;
	while(f>>client_name_read>>client_key_read)
	{
		if(client_name_read==client_name)
			flag=1;
	}
	f.close();
	//1表示存在，0表示不存在
	return flag;
}
bool check_client_to_client(string client_name1,string client_name2)
{
	fstream f;
	f.open("client_to_client.txt", ios::in);//打开文件，供读
	string client_name1_read,client_name2_read;
	bool flag=0;
	while(f>>client_name1_read>>client_name2_read)
	{
		if(client_name1_read==client_name1&&client_name2_read==client_name2)
			flag=1;
		else if(client_name1_read==client_name2&&client_name2_read==client_name1)
			flag=1;
	}
	f.close();
	return flag;
}
//将好友与好友写入文件
void write_client_to_client(string client_name1,string client_name2)
{
	fstream f;
	f.open("client_to_client.txt", ios::out | ios::app);
	f<<client_name1<<" "<<client_name2<<endl;
	f.close();
}
struct Client_to_client
{
	string client_name1;
	string client_name2;
};
vector<Client_to_client>get_back_client_to_client(string client_name1,string client_name2)
{
	vector<Client_to_client>q;
	q.clear();
	fstream f;
	f.open("client_to_client.txt", ios::in);//打开文件，供读
	string client_name1_read,client_name2_read;
	while(f>>client_name1_read>>client_name2_read)
	{
		Client_to_client a;
		a.client_name1=client_name1_read;
		a.client_name2=client_name2_read;
		q.push_back(a);
	}
	f.close();
	return q;
}
void delete_client_to_client(string client_name1,string client_name2)
{
	vector<Client_to_client>q=get_back_client_to_client(client_name1,client_name2);
	fstream f;
	int i;
	//改成覆盖式写入
	f.open("client_to_client.txt", ios::out);
	for(i=0;i<q.size();i++)
	{
		if(q[i].client_name1==client_name1&&q[i].client_name2==client_name2)continue;
		if(q[i].client_name1==client_name2&&q[i].client_name2==client_name1)continue;
		f<<q[i].client_name1<<" "<<q[i].client_name2<<endl;
	}
	f.close();
}
//子线程内容
DWORD WINAPI recv_msg(LPVOID lpParamter)
{
	//将传递过来的参数类型调整为整数型 
	Client t=*((Client*)lpParamter);
	char buf[200];
	CServerDlg * dlg = (CServerDlg *) AfxGetApp()->GetMainWnd();
	while(true)
	{
		memset(buf,0,sizeof(buf));
		int ret=recv(t.socket,buf,sizeof(buf),0);
		
	//	dlg->MessageBox("fmc");

		//为-1说明对方客户端无反应，客户端突然结束程序的情况
		if(ret==-1)
		{
			string client_name;
			CString name;
			int i;
			for(i=0;i<strlen(t.name);i++)
			{
				client_name+=t.name[i];
				name+=t.name[i];
			}
			
			dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+name+"]已下线");
			//标记下线
			client_vis[client_name]=false;

			break;
		}
		//判断用户是否存在，如果不存在说明在注册和登录界面周转
		if(check(t.socket)==false)
		{
			string name;
			string key;
			int i;
			memset(t.name,0,sizeof(t.name));
			for(i=2;i<strlen(buf);i++)
			{
				if(buf[i]==' ')break;
				name+=buf[i];
				t.name[i-2]=buf[i];
			}
			i++;
			for(;i<strlen(buf);i++)
			{
				key+=buf[i];
			}	
			CString cname;
			for(i=0;i<strlen(t.name);i++)
			cname+=t.name[i];
			//为注册指令
			if(buf[0]=='1')
			{
	
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+cname+"]申请注册");
				//看看这个账户是否被注册过
				int back=check_client(name,key);
				//说明被注册过，系统已经有了相同的账户名
				if(back==1||back==2)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：该账户名已经被注册");
					send(t.socket,"该账户名已经被注册",sizeof("该账户名已经被注册"),0);
				}
				else
				{
					//没被注册，写入文件，进行注册
					fstream  f;
					f.open("client_data.txt", ios::out | ios::app);
					f<<name<<" "<<key<<endl;
					f.close();
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：注册成功");
					send(t.socket,"注册成功",sizeof("注册成功"),0);
				}
			}
			//为登录指令
			else if(buf[0]=='2')
			{
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+cname+"]申请登录");
				int back=check_client(name,key);
				//登录成功
				if(back==1)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：登录成功");
					
					send(t.socket,"登录成功",sizeof("登录成功"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+cname+"]已经上线");
					//标记该用户上线
					client_vis[name]=t.socket;
					clients.push_back(t);
				}
				else if(back==2)
				{
					send(t.socket,"密码错误",sizeof("密码错误"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：密码错误");
				}
				else if(back==3)
				{
					send(t.socket,"用户不存在",sizeof("用户不存在"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：用户不存在");
				}
			}
		}
		else
		{
			if(strcmp(buf,"exit")==0)
			{
				CString name;
				string client_name;
				int i;
				for(i=0;i<strlen(t.name);i++)
				{
					name+=t.name[i];
					client_name+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+name+"]已下线");
				//从数组里删除下线用户信息
				for(i=0;i<clients.size();i++)
				{
					if(strcmp(clients[i].name,t.name)==0)
					{
						clients.erase(clients.begin()+i);
						break;
					}
				}
				//标记下线
				client_vis[client_name]=false;
				return NULL;
			}
			//此时表示要创建新群,传入参数为群名
			if(buf[0]=='1')
			{
				CString val,CSclient_name;
				string client_name,group_name;
				int i;
				for(i=2;i<strlen(buf);i++)
				{
					group_name+=buf[i];
					val+=buf[i];
				}
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name+=t.name[i];
					client_name+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name+"]申请建群，群名称："+val);
				int back=check_group(group_name);
				//说明该用户没有创建过相同名称的群
				if(back==1)
				{
					//将群名和用户名对应起来，写入文件
					write_group_to_client(group_name,client_name);
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：创建成功");
					send(t.socket,"3 创建成功",sizeof("3 创建成功"),0);
				}
				else
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：此群已经被创建过");
					send(t.socket,"3 此群已经被创建过，请另外选取群名",sizeof("3 此群已经被创建过，请另外选取群名"),0);
				}
			}
			//此时表示搜索加入群聊，传入的参数为群名
			else if(buf[0]=='2')
			{
				int i;
				string group_name;
				CString CSgroup_name;
				for(i=2;i<strlen(buf);i++)
				{
					CSgroup_name+=buf[i];
					group_name+=buf[i];
				}
				string client_name;
				CString CSclient_name;
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name+=t.name[i];
					client_name+=t.name[i];
				}

				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name+"]申请加入群聊，群名："+CSgroup_name);
				int back=check_group_to_client(group_name,client_name);
				if(back==1)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：该用户已存在此群");
					send(t.socket,"3 您已经存在此群",sizeof("3 您已经存在此群"),0);
				}
				//不在群里
				else if(back==2)
				{
					//将群名和用户名对应起来，写入文件
					write_group_to_client(group_name,client_name);
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：该用户成功加入此群");
					send(t.socket,"3 您已经成功加入此群",sizeof("3 您已经成功加入此群"),0);
				}
				else if(back==3)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：该用户搜索的群不存在");
					send(t.socket,"3 您搜索的群不存在",sizeof("3 您搜索的群不存在"),0);
				}

			}
			//此时为退出某个群聊，输入参数为要退出的群聊名字
			else if(buf[0]=='3')
			{
				int i;
				CString CSgroup_name;
				string group_name;
				for(i=2;i<strlen(buf);i++)
				{
					CSgroup_name+=buf[i];
					group_name+=buf[i];
				}
				CString CSclient_name;
				string client_name;
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name+=t.name[i];
					client_name+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name+"]申请退出群聊，群名："+CSgroup_name);
				delete_group_to_client(group_name,client_name);
				dlg->Print(Print_time()+" "+Print_ip(t)+" 反馈结果：退出成功");
				send(t.socket,"3 您已成功退出群聊",sizeof("3 您已成功退出群聊"),0);
			}
			//此时为用户开启了群聊模式，输入参数为群聊名称+发送信息内容
			else if(buf[0]=='4')
			{
				CString CSgroup_name;
				string group_name;
				CString CSval;
				int i;
				for(i=2;i<strlen(buf);i++)
				{
					if(buf[i]==' ')break;
					CSgroup_name+=buf[i];
					group_name+=buf[i];
				}
				i++;
				for(;i<strlen(buf);i++)
				{
					if(buf[i]==' ')break;
					CSval+=buf[i];
				}
				CString CSclient_name;
				string client_name;
				for(i=0;i<strlen(t.name);i++)
				{
						CSclient_name+=t.name[i];
						client_name+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name+"]通过群聊["+CSgroup_name+"]发送信息："+CSval);
				send_group_to_client(group_name,client_name,buf);
			}
			//表示在搜索添加好友，传入参数为好友姓名
			else if(buf[0]=='5')
			{
				CString CSclient_name1,CSclient_name2;
				string client_name1,client_name2;
				int i;
				for(i=2;i<strlen(buf);i++)
				{
					CSclient_name2+=buf[i];
					client_name2+=buf[i];
				}
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name1+=t.name[i];
					client_name1+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name1+"]申请添加好友["+CSclient_name2+"]");
				int back=check_is_client(client_name2);
				if(back==0)
				{
					dlg->Print("反馈结果：搜索的好友不存在");
					send(t.socket,"3 您搜索的好友不存在",sizeof("3 您搜索的好友不存在"),0);
				}
				else
				{
					back=check_client_to_client(client_name1,client_name2);
					if(back==1)
					{
						dlg->Print("反馈结果：该用户之前已经添加过该好友");
						send(t.socket,"3 您之前已经添加过好友",sizeof("3 您之前已经添加过好友"),0);
					}
					else
					{
						//将好友关系写入文件
						write_client_to_client(client_name1,client_name2);
						dlg->Print("反馈结果：添加成功");
						send(t.socket,"3 您已经成功添加好友",sizeof("3 您已经成功添加好友"),0);
					}
				}
			}
			//表示要删除好友，传入参数为将被删除的好友姓名
			else if(buf[0]=='6')
			{
				CString CSclient_name1,CSclient_name2;
				string client_name1,client_name2;
				int i;
				for(i=2;i<strlen(buf);i++)
				{
					CSclient_name2+=buf[i];
					client_name2+=buf[i];
				}
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name1+=t.name[i];
					client_name1+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name1+"]申请删除好友["+CSclient_name2+"]");
				delete_client_to_client(client_name1,client_name2);
				dlg->Print("反馈结果：删除成功");
				send(t.socket,"3 您已经成功删除好友",sizeof("3 您已经成功删除好友"),0);
			}
			//此时为私聊模式，传入信息为私聊的好友名字和聊天内容
			else if(buf[0]=='7')
			{
				CString CSclient_name1,CSclient_name2;
				string client_name1,client_name2;
				int i;
				for(i=2;i<strlen(buf);i++)
				{
					if(buf[i]==' ')break;
					CSclient_name2+=buf[i];
					client_name2+=buf[i];
				}
				i++;
				CString val;
				for(;i<strlen(buf);i++)
				{
					val+=buf[i];
				}
				for(i=0;i<strlen(t.name);i++)
				{
					CSclient_name1+=t.name[i];
					client_name1+=t.name[i];
				}
				dlg->Print(Print_time()+" "+Print_ip(t)+" 用户["+CSclient_name1+"]发送信息给好友["+CSclient_name2+"]，内容为："+val);
				strcat(buf," ");
				//切记加上这个，让对方知道是谁发来的信息
				strcat(buf,t.name);
				//发送信息
				send(client_vis[client_name2],buf,sizeof(buf),0);
			}
		//	else if(buf[0])
			int i;
			string client_name;
			for(i=0;i<strlen(t.name);i++)
				client_name+=t.name[i];
			/////把群组列表信息发送给客户端
			string group_list=get_group_list(client_name);
			char data[2000];
			memset(data,0,sizeof(data));
			//加上信息标记1
			strcat(data,"1 ");
			for(i=0;i<group_list.length();i++)
				data[i+2]=group_list[i];
			send(t.socket,data,sizeof(data),0);
			////把好友列表信息发送给客户端
			string friend_list=get_friend_list(client_name);
			memset(data,0,sizeof(data));
			//加上信息标记2
			strcat(data,"2 ");
			for(i=0;i<friend_list.length();i++)
				data[i+2]=friend_list[i];
			send(t.socket,data,sizeof(data),0);
		}
	}
	return NULL;
}