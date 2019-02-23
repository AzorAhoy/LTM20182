// TCPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#include "winsock2.h"
#include <fstream>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;
int main(int argc, char * argv[])
{
	//std::cout << "You have entered " << argc
		//<< " arguments:" << "\n";

	//for (int i = 0; i < argc; ++i)
	//std::cout << argv[i] << "\n";

	char port = *(argv[0]);
	//std::cout << "Hello World!\n"; 
	WSADATA wsaData;
	//Khoi tao WinSock 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Tao socket nghe ket noi tu Client
	SOCKET ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerAddr;
	//SOCKADDR_IN ClientAddr;
	//int ClientAddrLen;
	//int Port = 9000;

	//Khoi tao cau truc SOCKADDR_IN cua server
	//doi ket noi o cong 8888
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(port);
	
	//Bind socket cua server
	bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	//Chuyen sang trang thai doi ket noi
	listen(ListeningSocket, 5);
	//Chap nhan ket noi moi
	//ClientAddrLen = sizeof(ClientAddr);
	//NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen);
	SOCKET NewConnection = accept(ListeningSocket, NULL, NULL);
	//Sau khi chap nhan ket noi moi, server co the tiep tuc chap nhan
	//them cac ket noi khac, hoac gui nhan du lieu voi cac client
	//thong qua cac socket duoc accept voi client
	char buf[1024];
	int ret;
	//char filename[] = "Informacije.txt";
	char * filename = argv[2];
	//std::cout << argv[2];
	std::ifstream f(filename);

	if (f.is_open())
		std::cout << f.rdbuf();
	//printf("hello");

	fstream file;
	char* filename2 = argv[3];
	file.open(filename2, ios::out | ios::binary);

	while (true)
	{

		//printf("Hello");
		ret = recv(NewConnection, buf, sizeof(buf), 0);
		if (ret <= 0)
			//printf("Failed");
			break;

		buf[ret] = 0;
		//if (ret > 0)
			//printf("%i\n", ret);
		file << buf << "\r\n";
		printf("Received: %s\n", buf);
	}
	file.close();
	//Dong socket
	closesocket(NewConnection);
	closesocket(ListeningSocket);
	//Giai phong WinSock
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
