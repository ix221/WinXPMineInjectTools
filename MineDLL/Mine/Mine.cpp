// Mine.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "Mine.h"
#include "MineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMineApp

BEGIN_MESSAGE_MAP(CMineApp, CWinApp)
END_MESSAGE_MAP()


// CMineApp 构造

CMineApp::CMineApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMineApp 对象

CMineApp theApp;

const GUID CDECL _tlid = {0x832071f6,0x1a9f,0x453c,{0xb9,0xb5,0x22,0x91,0xb3,0x23,0x6f,0xaa}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


DWORD WINAPI DlgThreadCallBack(LPVOID lp) {
    MineDlg* Dlg;
    Dlg = new MineDlg();
    Dlg->DoModal();
    delete Dlg;
    FreeLibraryAndExitThread(theApp.m_hInstance, 1);
    return 0;
}
// CMineApp 初始化
BOOL CMineApp::InitInstance()
{
    CWinApp::InitInstance();
    ::CreateThread(NULL, NULL, DlgThreadCallBack, NULL, NULL, NULL);
    return TRUE;
}















//// DllGetClassObject - 返回类工厂
//
//STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	return AfxDllGetClassObject(rclsid, riid, ppv);
//}

//
//// DllCanUnloadNow - 允许 COM 卸载 DLL
//
//STDAPI DllCanUnloadNow(void)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	return AfxDllCanUnloadNow();
//}
//
//
//// DllRegisterServer - 将项添加到系统注册表
//
//STDAPI DllRegisterServer(void)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
//		return SELFREG_E_TYPELIB;
//
//	if (!COleObjectFactory::UpdateRegistryAll())
//		return SELFREG_E_CLASS;
//
//	return S_OK;
//}
//
//
//// DllUnregisterServer - 将项从系统注册表中移除
//
//STDAPI DllUnregisterServer(void)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
//		return SELFREG_E_TYPELIB;
//
//	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
//		return SELFREG_E_CLASS;
//
//	return S_OK;
//}
