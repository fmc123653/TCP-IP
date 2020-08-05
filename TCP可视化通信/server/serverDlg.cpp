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
	//��ÿ������Ԫ����ֵ
	server_val = (CEdit *)GetDlgItem(IDC_EDIT1);
	server_iport = (CEdit *)GetDlgItem(IDC_EDIT2);
	btn_makesure = (CButton *)GetDlgItem(IDC_BUTTON1);
	client_vis.clear();
	////
//	server_val->ReplaceSel("�ȴ��ͻ�������...\r\n");

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
//�ַ���ת����
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
//�������̺߳���
DWORD WINAPI recv_msg(LPVOID lpParamter); 
//�������̺߳���
DWORD WINAPI server_thd(LPVOID lpParamter); 
//����ͻ��˽ṹ��
struct Client
{
	int iport;
	SOCKET socket;
	char ip[20];
	char name[20];
};
//���崢��ͻ��˽ṹ��Ķ�̬����
vector<Client>clients;
void CServerDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString iport;
	server_iport->GetWindowText(iport);
	int iPort=CString_to_int(iport);

	HANDLE hThread = CreateThread(NULL, 0, server_thd,(LPVOID *)&iPort, 0, NULL);
    //���ﲻ�ǹر����̣߳����ǵ����̺߳�������ʱ���ͷ�ռ�õ��ڴ� 
    CloseHandle(hThread);
	//���������
	server_iport->SetReadOnly(TRUE);
	//������true�ĳ�false
	//������ť
	btn_makesure->EnableWindow(FALSE);
	//
	//CServerDlg * dlg = (CServerDlg *) AfxGetApp()->GetMainWnd();
	Print("�ѳɹ��������������ȴ��ͻ�������....");
}
DWORD WINAPI server_thd(LPVOID lpParamter)
{
	int iPort=*((int*)lpParamter);
	WSADATA wsaData;
	SOCKET sListen,
	sAccept;
	//�ͻ���ַ����
	int iLen;
	//�������Ϳͻ��ĵ�ַ
	struct sockaddr_in ser,
	cli;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
	//	MessageBox("Failed to load Winsock");
		return NULL;
	}
	//�������������׽ӿ�
	sListen=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
//		MessageBox("socket( ) Failed");
		return NULL;
	}
	//���½����������˵�ַ
	ser.sin_family=AF_INET;
	//htons( )������һ��˫�ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	ser.sin_port=htons(iPort);
	//htonl( )������һ�����ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	//ʹ��ϵͳָ���� IP ��ַ INADDR_ANY
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
//		MessageBox("bind( ) Failed");
		return NULL;
	}
	
	//�������״̬
	if(listen(sListen,5)==SOCKET_ERROR)
	{
	//	MessageBox("listen( ) Failed");
		return NULL;
	}
	//��ʼ���ͻ���ַ���Ȳ���
	iLen=sizeof(cli);
	//����һ������ѭ�����ȴ��ͻ�����������
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
		
		//ÿ�õ�һ���ͻ��˵����ӣ��͵����Ͽ���һ��������������������ͻ��˷�����Ϣ�����̺߳���
		HANDLE hThread = CreateThread(NULL, 0, recv_msg,(LPVOID *)&t, 0, NULL);
    	//���ﲻ�ǹر����̣߳����ǵ����̺߳�������ʱ���ͷ�ռ�õ��ڴ� 
    	CloseHandle(hThread);
	}
	closesocket(sAccept);
	closesocket(sListen);
	WSACleanup( );
	return NULL;
}
//����Ƿ��ڿͻ������У�������ھ�˵���ڽ���ע����¼
bool check(int socket)
{
	int i;
	for(i=0;i<clients.size();i++)
	{
		if(clients[i].socket==socket)return true;
	}
	return false;
}
//����˻�����
int check_client(string name,string key)
{
	fstream f;
	f.open("client_data.txt", ios::in);//���ļ�������
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
	CTime tim = CTime::GetCurrentTime(); ///����CTime���� 
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
	return "IP��ַ��"+ip+" �˿ںţ�"+iport+"\r\n";
}
int check_group(string group_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//���ļ�������
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
	//1˵�����Ⱥ��û������
	//2˵�����Ⱥ�Ѿ��������ˣ������ظ�������ͬ��Ⱥ��
	return result;
}
//��Ⱥ�����û����Ĺ�ϵд���ļ�
void write_group_to_client(string group_name,string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::out | ios::app);
	f<<group_name<<" "<<client_name<<endl;
	f.close();
}
//����Ⱥ��ʱ��������Ƿ�����˸�Ⱥ
int check_group_to_client(string group_name,string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//���ļ�������
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
	//1��ʾ��Ⱥ�2��ʾ����Ⱥ�3��ʾ���ҵ�Ⱥ������
	return result;
}
//���û���¼�ɹ�����Ҫ���û���Ӧ��Ⱥ����Ϣ����
string get_group_list(string client_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//���ļ�������
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
//���û���¼�ɹ�����Ҫ���û���Ӧ�ĺ�����Ϣ����
string get_friend_list(string client_name)
{
	fstream f;
	f.open("client_to_client.txt", ios::in);//���ļ�������
	string client_name1,client_name2;
	string friend_list; 
	while(f>>client_name1>>client_name2)
	{
		if(client_name1==client_name)
		{
			if(client_vis[client_name2]>0)
			friend_list+="<<����>>";
			else friend_list+="<<����>>";
			friend_list+="[";
			friend_list+=client_name2;
			friend_list+="]\r\n";
		}
		else if(client_name2==client_name)
		{
			if(client_vis[client_name1]>0)
			friend_list+="<<����>>";
			else friend_list+="<<����>>";
			friend_list+="[";
			friend_list+=client_name1;
			friend_list+="]\r\n";
		}
	}
	f.close();
	return friend_list;
}

//����ÿ��Ⱥ����Ҫ�������Ⱥ�ĳ�Ա���
string get_group_client(string group_name)
{
	fstream f;
	f.open("group_data.txt", ios::in);//���ļ�������
	string group_name_read,client_name_read;
	string result="";
	while(f>>group_name_read>>client_name_read)
	{
		if(group_name_read==group_name)
		{
			if(client_vis[client_name_read]>0)
			result+="<<����>>";
			else result+="<<����>>";
			result+="[";
			result+=client_name_read;
			result+="]\r\n";
		}
	}
	return result;
}

//�ò�������ɾ��Ⱥ����û���ϵ����ȡ������д��
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
	f.open("group_data.txt", ios::in);//���ļ�������
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
	//������Ҫ�ĳɲ�Ҫ׷�ӣ�����ԭ��������ʵ��ɾ��
	f.open("group_data.txt", ios::out);
	int i;
	for(i=0;i<q.size();i++)
	{
		//����ɾ��
		if(q[i].group_name==group_name&&q[i].client_name==client_name)continue;
		f<<q[i].group_name<<" "<<q[i].client_name<<endl;
	}
	f.close();
}
//��Ӧ����Ϣ���͸����Ⱥ��ÿ����Ա
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
			//��Ҫ����Ϣ�ظ������Լ�
			if(q[i].client_name==client_name)continue;
			send(client_vis[q[i].client_name],data,sizeof(data),0);
		}
	}
}

//������Ӻ���ʱ�жϺ����Ƿ����
bool check_is_client(string client_name)
{
	fstream f;
	f.open("client_data.txt", ios::in);//���ļ�������
	string client_name_read,client_key_read;
	bool flag=0;
	while(f>>client_name_read>>client_key_read)
	{
		if(client_name_read==client_name)
			flag=1;
	}
	f.close();
	//1��ʾ���ڣ�0��ʾ������
	return flag;
}
bool check_client_to_client(string client_name1,string client_name2)
{
	fstream f;
	f.open("client_to_client.txt", ios::in);//���ļ�������
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
//�����������д���ļ�
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
	f.open("client_to_client.txt", ios::in);//���ļ�������
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
	//�ĳɸ���ʽд��
	f.open("client_to_client.txt", ios::out);
	for(i=0;i<q.size();i++)
	{
		if(q[i].client_name1==client_name1&&q[i].client_name2==client_name2)continue;
		if(q[i].client_name1==client_name2&&q[i].client_name2==client_name1)continue;
		f<<q[i].client_name1<<" "<<q[i].client_name2<<endl;
	}
	f.close();
}
//���߳�����
DWORD WINAPI recv_msg(LPVOID lpParamter)
{
	//�����ݹ����Ĳ������͵���Ϊ������ 
	Client t=*((Client*)lpParamter);
	char buf[200];
	CServerDlg * dlg = (CServerDlg *) AfxGetApp()->GetMainWnd();
	while(true)
	{
		memset(buf,0,sizeof(buf));
		int ret=recv(t.socket,buf,sizeof(buf),0);
		
	//	dlg->MessageBox("fmc");

		//Ϊ-1˵���Է��ͻ����޷�Ӧ���ͻ���ͻȻ������������
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
			
			dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+name+"]������");
			//�������
			client_vis[client_name]=false;

			break;
		}
		//�ж��û��Ƿ���ڣ����������˵����ע��͵�¼������ת
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
			//Ϊע��ָ��
			if(buf[0]=='1')
			{
	
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+cname+"]����ע��");
				//��������˻��Ƿ�ע���
				int back=check_client(name,key);
				//˵����ע�����ϵͳ�Ѿ�������ͬ���˻���
				if(back==1||back==2)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" ������������˻����Ѿ���ע��");
					send(t.socket,"���˻����Ѿ���ע��",sizeof("���˻����Ѿ���ע��"),0);
				}
				else
				{
					//û��ע�ᣬд���ļ�������ע��
					fstream  f;
					f.open("client_data.txt", ios::out | ios::app);
					f<<name<<" "<<key<<endl;
					f.close();
					dlg->Print(Print_time()+" "+Print_ip(t)+" ���������ע��ɹ�");
					send(t.socket,"ע��ɹ�",sizeof("ע��ɹ�"),0);
				}
			}
			//Ϊ��¼ָ��
			else if(buf[0]=='2')
			{
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+cname+"]�����¼");
				int back=check_client(name,key);
				//��¼�ɹ�
				if(back==1)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" �����������¼�ɹ�");
					
					send(t.socket,"��¼�ɹ�",sizeof("��¼�ɹ�"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+cname+"]�Ѿ�����");
					//��Ǹ��û�����
					client_vis[name]=t.socket;
					clients.push_back(t);
				}
				else if(back==2)
				{
					send(t.socket,"�������",sizeof("�������"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" ����������������");
				}
				else if(back==3)
				{
					send(t.socket,"�û�������",sizeof("�û�������"),0);
					dlg->Print(Print_time()+" "+Print_ip(t)+" ����������û�������");
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+name+"]������");
				//��������ɾ�������û���Ϣ
				for(i=0;i<clients.size();i++)
				{
					if(strcmp(clients[i].name,t.name)==0)
					{
						clients.erase(clients.begin()+i);
						break;
					}
				}
				//�������
				client_vis[client_name]=false;
				return NULL;
			}
			//��ʱ��ʾҪ������Ⱥ,�������ΪȺ��
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name+"]���뽨Ⱥ��Ⱥ���ƣ�"+val);
				int back=check_group(group_name);
				//˵�����û�û�д�������ͬ���Ƶ�Ⱥ
				if(back==1)
				{
					//��Ⱥ�����û�����Ӧ������д���ļ�
					write_group_to_client(group_name,client_name);
					dlg->Print(Print_time()+" "+Print_ip(t)+" ��������������ɹ�");
					send(t.socket,"3 �����ɹ�",sizeof("3 �����ɹ�"),0);
				}
				else
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" �����������Ⱥ�Ѿ���������");
					send(t.socket,"3 ��Ⱥ�Ѿ�����������������ѡȡȺ��",sizeof("3 ��Ⱥ�Ѿ�����������������ѡȡȺ��"),0);
				}
			}
			//��ʱ��ʾ��������Ⱥ�ģ�����Ĳ���ΪȺ��
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

				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name+"]�������Ⱥ�ģ�Ⱥ����"+CSgroup_name);
				int back=check_group_to_client(group_name,client_name);
				if(back==1)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" ������������û��Ѵ��ڴ�Ⱥ");
					send(t.socket,"3 ���Ѿ����ڴ�Ⱥ",sizeof("3 ���Ѿ����ڴ�Ⱥ"),0);
				}
				//����Ⱥ��
				else if(back==2)
				{
					//��Ⱥ�����û�����Ӧ������д���ļ�
					write_group_to_client(group_name,client_name);
					dlg->Print(Print_time()+" "+Print_ip(t)+" ������������û��ɹ������Ⱥ");
					send(t.socket,"3 ���Ѿ��ɹ������Ⱥ",sizeof("3 ���Ѿ��ɹ������Ⱥ"),0);
				}
				else if(back==3)
				{
					dlg->Print(Print_time()+" "+Print_ip(t)+" ������������û�������Ⱥ������");
					send(t.socket,"3 ��������Ⱥ������",sizeof("3 ��������Ⱥ������"),0);
				}

			}
			//��ʱΪ�˳�ĳ��Ⱥ�ģ��������ΪҪ�˳���Ⱥ������
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name+"]�����˳�Ⱥ�ģ�Ⱥ����"+CSgroup_name);
				delete_group_to_client(group_name,client_name);
				dlg->Print(Print_time()+" "+Print_ip(t)+" ����������˳��ɹ�");
				send(t.socket,"3 ���ѳɹ��˳�Ⱥ��",sizeof("3 ���ѳɹ��˳�Ⱥ��"),0);
			}
			//��ʱΪ�û�������Ⱥ��ģʽ���������ΪȺ������+������Ϣ����
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name+"]ͨ��Ⱥ��["+CSgroup_name+"]������Ϣ��"+CSval);
				send_group_to_client(group_name,client_name,buf);
			}
			//��ʾ��������Ӻ��ѣ��������Ϊ��������
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name1+"]������Ӻ���["+CSclient_name2+"]");
				int back=check_is_client(client_name2);
				if(back==0)
				{
					dlg->Print("��������������ĺ��Ѳ�����");
					send(t.socket,"3 �������ĺ��Ѳ�����",sizeof("3 �������ĺ��Ѳ�����"),0);
				}
				else
				{
					back=check_client_to_client(client_name1,client_name2);
					if(back==1)
					{
						dlg->Print("������������û�֮ǰ�Ѿ���ӹ��ú���");
						send(t.socket,"3 ��֮ǰ�Ѿ���ӹ�����",sizeof("3 ��֮ǰ�Ѿ���ӹ�����"),0);
					}
					else
					{
						//�����ѹ�ϵд���ļ�
						write_client_to_client(client_name1,client_name2);
						dlg->Print("�����������ӳɹ�");
						send(t.socket,"3 ���Ѿ��ɹ���Ӻ���",sizeof("3 ���Ѿ��ɹ���Ӻ���"),0);
					}
				}
			}
			//��ʾҪɾ�����ѣ��������Ϊ����ɾ���ĺ�������
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name1+"]����ɾ������["+CSclient_name2+"]");
				delete_client_to_client(client_name1,client_name2);
				dlg->Print("���������ɾ���ɹ�");
				send(t.socket,"3 ���Ѿ��ɹ�ɾ������",sizeof("3 ���Ѿ��ɹ�ɾ������"),0);
			}
			//��ʱΪ˽��ģʽ��������ϢΪ˽�ĵĺ������ֺ���������
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
				dlg->Print(Print_time()+" "+Print_ip(t)+" �û�["+CSclient_name1+"]������Ϣ������["+CSclient_name2+"]������Ϊ��"+val);
				strcat(buf," ");
				//�мǼ���������öԷ�֪����˭��������Ϣ
				strcat(buf,t.name);
				//������Ϣ
				send(client_vis[client_name2],buf,sizeof(buf),0);
			}
		//	else if(buf[0])
			int i;
			string client_name;
			for(i=0;i<strlen(t.name);i++)
				client_name+=t.name[i];
			/////��Ⱥ���б���Ϣ���͸��ͻ���
			string group_list=get_group_list(client_name);
			char data[2000];
			memset(data,0,sizeof(data));
			//������Ϣ���1
			strcat(data,"1 ");
			for(i=0;i<group_list.length();i++)
				data[i+2]=group_list[i];
			send(t.socket,data,sizeof(data),0);
			////�Ѻ����б���Ϣ���͸��ͻ���
			string friend_list=get_friend_list(client_name);
			memset(data,0,sizeof(data));
			//������Ϣ���2
			strcat(data,"2 ");
			for(i=0;i<friend_list.length();i++)
				data[i+2]=friend_list[i];
			send(t.socket,data,sizeof(data),0);
		}
	}
	return NULL;
}