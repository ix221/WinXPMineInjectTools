// MineDlg.cpp: 实现文件
//

#include "pch.h"
#include "Mine.h"
#include "MineDlg.h"
#include "afxdialogex.h"


// MineDlg 对话框

IMPLEMENT_DYNAMIC(MineDlg, CDialog)

MineDlg::MineDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

MineDlg::~MineDlg()
{
}

void MineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MineDlg, CDialog)
    ON_BN_CLICKED(IDOK2, &MineDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDOK3, &MineDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDOK4, &MineDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDOK5, &MineDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// MineDlg 消息处理程序
DWORD GetBaseAddr() {
    HMODULE hMode = GetModuleHandle(nullptr);
    //LPWSTR s = (LPWSTR)malloc(0x100);
    //wsprintf(s, L"基址:%p", hMode);
    //AfxMessageBox(s);
    return (DWORD)hMode;
}

void MineDlg::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    auto BaseAddr = GetBaseAddr();
    DWORD TimeOffset = 0x579C;
    DWORD TimeInsOffset = 0x2FF5;
    DWORD InsLen = 6;
    DWORD old;
    VirtualProtect((void*)(BaseAddr + TimeInsOffset), InsLen, PAGE_EXECUTE_READWRITE, &old);
    BYTE INS[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
    memcpy((void*)(BaseAddr + TimeInsOffset), INS, InsLen);
    VirtualProtect((void*)(BaseAddr + TimeInsOffset), InsLen, old, &old);
}


void MineDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    auto BaseAddr = GetBaseAddr();
    DWORD TimeOffset = 0x579C;
    DWORD TimeInsOffset = 0x2FF5;
    DWORD InsLen = 6;
    DWORD old;
    VirtualProtect((void*)(BaseAddr + TimeInsOffset), InsLen, PAGE_EXECUTE_READWRITE, &old);
    BYTE INS[] = { 0xFF,0x05,0x9C,0x57,0x00,0x01 };
    memcpy((void*)(BaseAddr + TimeInsOffset), INS, 6);
    VirtualProtect((void*)(BaseAddr + TimeInsOffset), InsLen, old, &old);

}


void MineDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    DWORD ESPOffset = 0x2f80;
    DWORD FuncAddr = GetBaseAddr() + ESPOffset;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FuncAddr, NULL, 0, NULL);
}


void MineDlg::OnBnClickedButton4()
{
    // TODO: 在此添加控件通知处理程序代码
    DWORD ESPOffset = 0x347C;
    DWORD FuncAddr = GetBaseAddr() + ESPOffset;
    struct { int a; } s = { 0 };
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)FuncAddr, &s, NULL, NULL);

}
