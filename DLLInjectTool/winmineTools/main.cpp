#include<windows.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<TlHelp32.h>
DWORD FindProcess() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32 = { sizeof(pe32) };
    BOOL ret = Process32First(hSnap, &pe32);
    while (ret)
    {
        if (!wcsncmp(pe32.szExeFile, L"winmine.exe", 11)) {
            printf("Find winmine.exe Process %d\n", pe32.th32ProcessID);
            return pe32.th32ProcessID;
        }
        ret = Process32Next(hSnap, &pe32);
    }
    return 0;
}
void Inject(DWORD ProcessId, const char* szPath)
{
    //1.��Ŀ����̻�ȡ���
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
    printf("���̾��:%p\n", hProcess);
    //2.��Ŀ�������������ռ�
    LPVOID lpAddress = VirtualAllocEx(hProcess, NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    //3.д��DLL·��
    SIZE_T dwWriteLength = 0;
    WriteProcessMemory(hProcess, lpAddress, szPath, strlen(szPath), &dwWriteLength);
    //4.����Զ���̣߳��ص�����ʹ�� LoadLibrary ����ָ�� dll
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpAddress, NULL, NULL);
    //5.�ȴ����أ�loadLibrary���أ�
    WaitForSingleObject(hThread, -1);
    //6.�ͷſռ�
    VirtualFreeEx(hProcess, lpAddress, 0, MEM_RELEASE);
    //7.�ͷž��
    CloseHandle(hProcess);
    CloseHandle(hThread);
}

int main() {
    DWORD ProcessId = FindProcess();
    while (!ProcessId) {
        printf("δ�ҵ�ɨ�׳��򣬵ȴ�����������\n");
        Sleep(2000);
        ProcessId = FindProcess();
    }
    printf("��ʼע�����...\n");
    Inject(ProcessId, "E:\\CODE\\wimine\\Mine\\release\\Mine.dll");
    printf("ע�����\n");

}