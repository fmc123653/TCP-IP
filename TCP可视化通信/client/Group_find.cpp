// Group_find.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Group_find.h"
#include "clientDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Group_find dialog


Group_find::Group_find(CWnd* pParent /*=NULL*/)
	: CDialog(Group_find::IDD, pParent)
{
	//{{AFX_DATA_INIT(Group_find)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Group_find::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Group_find)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Group_find, CDialog)
	//{{AFX_MSG_MAP(Group_find)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Group_find message handlers

BOOL Group_find::OnInitDialog() 
{
	CDialog::OnInitDialog();
	group_number = (CEdit *)GetDlgItem(IDC_EDIT1);
	btn_group_find = (CButton *)GetDlgItem(IDC_BUTTON1);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Group_find::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CClientDlg* parent = (CClientDlg*)GetParent();
	SOCKET sClient=parent->SClient;
	char buf[2000];
	CString val;
	group_number->GetWindowText(val);
	int i;
	memset(buf,0,sizeof(buf));
	//指令2表示搜索加群
	strcat(buf,"2 ");
	for(i=0;i<val.GetLength();i++)
		buf[i+2]=val[i];
	send(sClient,buf,sizeof(buf),0);

	memset(buf,0,sizeof(buf));
	recv(sClient,buf,sizeof(buf),0);
	val="";
	for(i=0;i<int(strlen(buf));i++)
		val+=buf[i];
	MessageBox("服务器反馈结果："+val);
	//接收列表信息
	memset(buf,0,sizeof(buf));
	CString result;
	recv(sClient,buf,sizeof(buf),0);
	result="";
	for(i=0;i<int(strlen(buf));i++)
	{
		if(i==0)
			result+="[";
		if(buf[i]==' ')
		{
			result+="]\r\n\r\n";
			if(i!=int(strlen(buf)-1))
				result+="[";
		}	
		else result+=buf[i];
	}
	parent->group_list->SetWindowText(result);

}
