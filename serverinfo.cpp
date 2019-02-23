// serverinfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "winsock2.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

struct sysInfo {
	char name[32];
	int n;
};

int main(int argc, char * argv[])
{
	//std::cout << "You have entered " << argc
		//<< " arguments:" << "\n";

	//for (int i = 0; i < argc; ++i)
	//std::cout << argv[i] << "\n";
	//char * ADDR = argv[1];
	char port = *(argv[1]);
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9000);
	//system("PAUSE");
	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	SOCKET client = accept(listener, NULL, NULL);

	char buf[256];
	int ret = recv(client, buf, sizeof(buf), 0);

	buf[ret] = 0;
	printf("Received: %s\n", buf);

	struct sysInfo si;
	memcpy(&si, buf, sizeof(si));
	printf("%s\n", si.name);
	printf("%i\n", si.n);
	int d;
	//char buf2[1024];
	while (true)
	{
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
		{
			break;
		}
		buf[ret] = 0;
		printf("Received: %s\n", buf);
	}
	closesocket(client);
	closesocket(listener);
	system("PAUSE");
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
