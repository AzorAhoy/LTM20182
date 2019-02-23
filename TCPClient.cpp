// TCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <fstream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

int main(int argc, char * argv[])
{
	//cout << "You have entered " << argc
	//	<< " arguments:" << "\n";

	//for (int i = 0; i < argc; ++i)
	//	cout << argv[i] << "\n";
    //std::cout << "Hello World!\n"; 
	WSADATA wsaData;
	
	//Khoi tao Winsock 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//Tao socket client
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//Khoi tao cau truc SOCKADDR_IN
	//co dia chi 202.191.56.69, cong 8888
	SOCKADDR_IN addr;
	int Port = *(argv[0]);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(Port);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	

	system("PAUSE");

	int ret = connect(s, (SOCKADDR *) &addr, sizeof(addr));

	char buf[1024];
	fstream file;
	file.open("client.txt", ios::out | ios::binary);
	while (true)
	{

		printf("Nhap du lieu: ");
		gets_s(buf, sizeof(buf));
		int t = send(s, buf, strlen(buf), 0);
		file << buf<<"\r\n";
		//file << endl;
		
		if (strncmp(buf, "exit", 4) == 0)
			break;
		
	}
	file.close();
	closesocket(s);
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
