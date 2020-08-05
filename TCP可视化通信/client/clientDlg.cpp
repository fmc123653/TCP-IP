// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
//����⺯��
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
	//ÿ���ؼ���Ӧ��ֵ
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
	//��������ip��ַ�Ͷ˿ںŵ�һ���������ڰ�ť,�����ӳɹ��ٽ���
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
//����ȫ�ֵĿͻ�����ʽ�׽ӿ�
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
		MessageBox("����ȷ����ip��ַ�Ͷ˿ں�");
		return;
	}
	int iport =CString_to_int(Iport);
	WSADATA wsaData;
	
	//�������˵�ַ
	struct sockaddr_in ser;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		MessageBox("Failed to load Winsock");
		return;
	}
	//��дҪ���ӵķ�������ַ��Ϣ
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iport);
	//inet_addr( )�����������еĵ�� IP ��ַת��Ϊ�ö����Ʊ�ʾ�������ֽ�˳��� IP ��ַ
	ser.sin_addr.s_addr=inet_addr(ip);
	//�����ͻ�����ʽ�׽ӿ�
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if(sClient==INVALID_SOCKET)
	{
		MessageBox("socket( ) Failed");
		return;
	}
	//��ֵ
	SClient=sClient;
	//������������˽��� TCP ����
	if(connect(sClient,(struct sockaddr*)&ser,sizeof(ser))==INVALID_SOCKET)
	{
		MessageBox("connect( ) Failed");
		return;
	}
	else
	{
		MessageBox("���ӳɹ�");
		//���������ip��ַ�ı�������
		client_ip->SetReadOnly(TRUE);
		//��������Ķ˿ں��ı�������
		client_iport->SetReadOnly(TRUE);
		//������true�ĳ�false
		//������ť
		btn_connect->EnableWindow(FALSE);

		//��ע���¼��ؽ���
		client_name->SetReadOnly(FALSE);
		client_key->SetReadOnly(FALSE);
		btn_register->EnableWindow(TRUE);
		btn_login->EnableWindow(TRUE);
	//	btn_exit->EnableWindow(TRUE);
	}
//	int 
//	MessageBox(iport);
}
//ע�ᰴť
void CClientDlg::OnButton2() 
{

	// TODO: Add your control notification handler code here
	CString CSname,CSkey;
	//���е�¼��������ĸ�ֵ
	client_name->GetWindowText(CSname);
	client_key->GetWindowText(CSkey);
	if(CSname=="" || CSkey=="")
	{
		MessageBox("����ȷ����ע��������ע������");
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
	MessageBox("���������������"+result);
	if(result!="ע��ɹ�")return;
}
//ר��������ʾȺ���б���Ϣ�ĺ���
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
	//��ʾ
	dlg->group_list->SetWindowText(result);
}
//��ӡ�����б���Ϣ
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
//��ӡ���������������Ϣ
void Print_Message(char *buf)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CString result;
	int i;
	for(i=0;i<strlen(buf);i++)
		result+=buf[i];
	dlg->MessageBox("���������������"+result);
}
CString Print_time()
{
	CTime tim = CTime::GetCurrentTime(); ///����CTime���� 
	CString Tim = tim.Format("%Y-%m-%d %H:%M:%S");  
	return Tim;
}
//��ӡ������˵��������
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
		//˵����ǰ���û�û���������Ⱥ���죬���Բ���ʾ
		if(CSgroup_name!=CSgroup_name2)
			return;
	}
	else if(Model=='7')
	{
		CString CSclient_name;
		dlg->client_name->GetWindowText(CSclient_name);
		//˵����ǰ˽�ĵ������������
		if(CSgroup_name!=CSclient_name)
			return;
	}
	//��ʾ��������
	dlg->chat_val->ReplaceSel("["+CSclient_name+"] "+Print_time()+"\r\n "+CSval+"\r\n\r\n");
}
//��ӡ�Լ�˵�Ļ�
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
	//���е�¼��������ĸ�ֵ
	client_name->GetWindowText(CSname);
	client_key->GetWindowText(CSkey);
	if(CSname=="" || CSkey=="")
	{
		MessageBox("����ȷ�����¼�����͵�¼����");
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
	//����2�÷������ж�ָ��
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
	MessageBox("���������������"+result);
	
	if(strcmp(buf,"��¼�ɹ�")!=0)return;


	//����һ���߳��������ո�����Ϣ�������Ϳ���ʵ��ʵʱ���½�����Ϣ��
	HANDLE hThread = CreateThread(NULL, 0, recv_msg,(LPVOID *)&sClient, 0, NULL);
    //���ﲻ�ǹر����̣߳����ǵ����̺߳�������ʱ���ͷ�ռ�õ��ڴ� 
    CloseHandle(hThread);

	//������ť
	btn_login->EnableWindow(FALSE);
	btn_register->EnableWindow(FALSE);
	//�����ı���
	client_name->SetReadOnly(TRUE);
	client_key->SetReadOnly(TRUE);
	//�����˳���ť
	btn_exit->EnableWindow(TRUE);
	//����
	btn_group_create->EnableWindow(TRUE);
	btn_group_find->EnableWindow(TRUE);
	btn_friend_find->EnableWindow(TRUE);
	btn_group_chat->EnableWindow(TRUE);
	btn_friend_chat->EnableWindow(TRUE);
	group_chat_edit->SetReadOnly(FALSE);
	friend_chat_edit->SetReadOnly(FALSE);
}
//���߳�����
DWORD WINAPI recv_msg(LPVOID lpParamter)
{
	CClientDlg * dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	//�����ݹ����Ĳ������͵���Ϊ������ 
	SOCKET socket=*((SOCKET*)lpParamter);
	char buf[2000];
	while(true)
	{
		memset(buf,0,sizeof(buf));
		int ret=recv(sClient,buf,sizeof(buf),0);
		//��ʾ�Է��޷�Ӧ
		if(ret==-1)
		{
			return NULL;
		}
		//����������������־
		//buf[0]Ϊ1����ӡ�����б���Ϣ
		//buf[0]Ϊ2����ӡ�����б���Ϣ
		//buf[0]Ϊ3����ӡ�����������������
		//buf[0]Ϊ4����ӡͨ��Ⱥ�ķ���������Ϣ
		//buf[0]Ϊ5����ӡͨ��˽�ķ���������Ϣ
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
	//���������ip��ַ�ı�������
	client_ip->SetReadOnly(FALSE);
	//��������Ķ˿ں��ı�������
	client_iport->SetReadOnly(FALSE);
	//������true�ĳ�false
	//������ť
	btn_connect->EnableWindow(TRUE);

	//��ע���¼��ؽ���
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

	//�������
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
//������Ӻ���
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
//��������������浱ǰ����ģʽ
void CClientDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CString CSgroup_name;
	group_chat_edit->GetWindowText(CSgroup_name);
	model->SetWindowText("Ⱥ��");
	group_name->SetWindowText(CSgroup_name);
	chat_val->SetWindowText("");

}
//������Ϣ��������һ��
void CClientDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CString Model;
	model->GetWindowText(Model);
	//������һ��ʼ�����ʱ���е�������ˣ�˵��һ�£�CSgroup_nameΪȺ��ģʽʱָȺ�����֣�˽��ģʽΪ��������
	CString CSgroup_name;
	group_name->GetWindowText(CSgroup_name);
	CString val;
	send_val->GetWindowText(val);
	char buf[2000];
	memset(buf,0,sizeof(buf));
	if(Model=="Ⱥ��")
		strcat(buf,"4 ");
	else if(Model=="˽��")
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
//����Ⱥ��
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
	model->SetWindowText("˽��");
	CString CSclient_name;
	friend_chat_edit->GetWindowText(CSclient_name);
	group_name->SetWindowText(CSclient_name);
	chat_val->SetWindowText("");
}

