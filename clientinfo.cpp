// clientinfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

struct sysInfo {
	char name[32];
	int n;
};

int main(int argc, char * argv[])
{

	TCHAR buffer[256] = TEXT("");
	TCHAR szDescription[8][32] = { TEXT("NetBIOS"),
		TEXT("DNS hostname"),
		TEXT("DNS domain"),
		TEXT("DNS fully-qualified"),
		TEXT("Physical NetBIOS"),
		TEXT("Physical DNS hostname"),
		TEXT("Physical DNS domain"),
		TEXT("Physical DNS fully-qualified") };
	int cnf = 0;
	DWORD dwSize = sizeof(buffer);

	for (cnf = 0; cnf < ComputerNameMax; cnf++)
	{
		if (!GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize))
		{
			_tprintf(TEXT("GetComputerNameEx failed (%d)\n"), GetLastError());
			//return;
		}
		else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);

		dwSize = _countof(buffer);
		ZeroMemory(buffer, dwSize);
	}
	printf_s("%c\n", (char *)buffer);
	
	DWORD mydrives = 100;// buffer length
	wchar_t lpBuffer[100];// buffer for drive string storage
	//char lpBuffer[100];
	DWORD test = GetLogicalDriveStrings(mydrives, lpBuffer);

	printf("The logical drives of this machine are:\n\n");
	//char * b = (char*)lpBuffer;
	//std::cout << lpBuffer;
	for (int i = 0; i < sizeof(lpBuffer); i++) {
		//if ((char *) lpBuffer[i] >= "a" && (char *)  lpBuffer[i] <= "Z")
		//{
		printf("%c", lpBuffer[i]);
		//}
	}

	printf("\n");

	char * host = argv[1];
	char * port = argv[2];
	//std::cout << host<<"  "<<port;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host);
	addr.sin_port = htons(9000);
	
	//system("PAUSE");



	int ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));
	struct sysInfo si;
	strcpy(si.name, "erfrefrefr");
	si.n = 26;

	send(client, (char *)&si, sizeof(si), 0);
	int n;
	char buf[1024];
	while (true)
	{
		printf("Nhap du lieu: ");
		gets_s(buf, sizeof(buf));
		int t = send(client, buf, strlen(buf), 0);
		//file << buf << "\r\n";
		//file << endl;

		if (strncmp(buf, "exit", 4) == 0)
			break;
	}
	closesocket(client);
	WSACleanup();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
