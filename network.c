




bool Client_ConnectTo(unsigned short Port, unsigned int IP, int* Socket)
{
	int			Sockfd = -1;
	struct sockaddr_in	SockAddress;
	// NONBLOCK
	int			File_Status_Flag = 0;
	int			valopt; 
	socklen_t		lon; 

	if(IP==INADDR_BROADCAST)	IP=INADDR_ANY;

	if((Sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
	{
		perror("open socket error");
		return false;
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
		close(sock);
		return false;
	}

	if(Socket)
	{
		*Socket = Sockfd;
	}
	else
	{
		close(sock);	
	}
	return true;
}
