#include <stdio.h>		//perror()
#include <sys/types.h>		//socket(), connect()
#include <sys/socket.h>		//socket(), connect()
#include <string.h>		//bzero()
#include <arpa/inet.h>		//htons()
#include <sys/socket.h>		//inet_aton()
#include <netinet/in.h>		//inet_aton()
#include <arpa/inet.h>		//inet_aton()
#include <unistd.h>		//close()

int Client_ConnectTo(unsigned short Port, unsigned int IP, int* Socket)
{
	int			Sockfd = -1;
	struct sockaddr_in	SockAddress;

	if(IP==INADDR_BROADCAST)	IP=INADDR_ANY;
	if((Sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
	{
		perror("open socket error");
		return 0;
	}

	bzero(&SockAddress, sizeof(struct sockaddr_in));
	SockAddress.sin_family = AF_INET;
	SockAddress.sin_port = htons(Port);

	//listen on LOCALHOST
	inet_aton("127.0.0.1", &SockAddress.sin_addr);
	//listen on certain ip address
	if(IP!=INADDR_ANY)
	{
		SockAddress.sin_addr.s_addr = IP;
	}

	//connection stablish
	if(connect(Sockfd, (struct sockaddr *)&SockAddress, sizeof(struct sockaddr)) == -1)
	{
		perror("Client connect to server error");
		close(Sockfd);
		return 0;
	}

	if(Socket)
	{
		*Socket = Sockfd;
	}
	else
	{
		close(Sockfd);
	}
	return 1;
}
