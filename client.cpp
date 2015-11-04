#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SERV_IP "192.168.43.168"
#define port 8080

using namespace std;

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	char message[] = "Hello, Hello, Hey!";
	char buff[1024];
	int res, ServSock;
	struct sockaddr_in ServAddr;
	memset(&ServAddr, 0, sizeof(ServAddr));
	/*ServAddr.sin_family = PF_INET;
	ServAddr.sin_port = port;
	res = inet_pton(PF_INET, SERV_IP, &ServAddr.sin_addr);
	ServSock = socket(ServAddr.sin_family, SOCK_STREAM, PF_INET);*/
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(port);
	ServAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	res = inet_pton(AF_INET, SERV_IP, &ServAddr.sin_addr);
	ServSock = socket(ServAddr.sin_family, SOCK_STREAM, 0);
	if (connect(ServSock,  (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0) {
		cout << "Ошибка: соединения";
		close(sock);
		return 1;
	}
	while (1)
	{
        cin >> message;
        send(ServSock, message, sizeof(message), 0);
        int b_recv;
        b_recv = recv(ServSock, buff, sizeof(buff), 0);
        cout << buff << "\n";
	}
	return 0;
}

