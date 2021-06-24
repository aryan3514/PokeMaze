#include<stdio.h>
#include<winsock2.h>
#include <iostream>
using namespace std;


#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA wsa;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.");

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET) {
		cerr << "error" << endl;
		return 1;
	}  

	sockaddr_in binder;
	binder.sin_family = AF_INET;
	binder.sin_port = htons(54000);
	binder.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&binder, sizeof(binder));


	listen(listening, SOMAXCONN);

	sockaddr_in client;

	int client_size = sizeof(client);
	
	SOCKET client_socket = accept(listening, (sockaddr*)&client, &client_size);

	closesocket(listening);
	WSACleanup();
	return 0;
}