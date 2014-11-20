#include <stdio.h>		//perror()
#include <sys/types.h>		//socket(), connect()
#include <sys/socket.h>		//socket(), connect()
#include <string.h>		//memset()
#include <arpa/inet.h>		//htons()
#include <sys/socket.h>		//inet_aton()
#include <netinet/in.h>		//inet_aton()
#include <arpa/inet.h>		//inet_aton()
#include <sys/select.h>		//FD_ZERO(), FD_SET(), select()
#include <stdlib.h>		//exit()
#include <unistd.h>		//close()
#include <ctype.h>		//isprint()
#include <strings.h>		//strncasecmp()

#include "rsp.h"


#define	_DEBUG_

int main(void)
{
	int			sock, maxfd;
	fd_set			readset, writeset;
	int			result;
	RSP_Message		msg;

#ifdef	_DEBUG_
	int			i;
	unsigned char		string[16];
#endif	//_DEBUG_

	Client_ConnectTo(PORT_NUMBER, INADDR_ANY, &sock);

	while(1)
	{
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		maxfd  = sock;
		FD_SET(sock, &readset);
		FD_SET(sock, &writeset);

		if(select(maxfd+1, &readset, &writeset, NULL, NULL) < 0)
		{
			perror("select");
			close(sock);
			exit(-2);
		}

		if(FD_ISSET(sock, &readset))
		{
			result = recv(sock, &msg.Size, sizeof(msg.Size), 0);
			msg.Size = htonl(msg.Size);
			if(result != sizeof(msg.Size)) continue;
#ifdef	_DEBUG_
			printf("message size = %u\n", msg.Size);
#endif	//_DEBUG_
			msg.Message = calloc(1, msg.Size+1);
			result = recv(sock, msg.Message, msg.Size, 0);

#ifdef	_DEBUG_
			memset(string, 0, sizeof(string));
			for(i=0;i<result;i++)
			{
				if(i%8==0)	printf("%s\n%03X(%04d)\t", string, i, i);
				printf("%02X(%03d) ",  msg.Message[i],  msg.Message[i]);
				string[i%8]=(isprint(msg.Message[i])? msg.Message[i]:'.');
			}
			printf("%s\n", string);

			printf("Got : %s\n", msg.Message);
#endif	//_DEBUG_

			if(strncasecmp(msg.Message, MSG_TYPE_UPDATE, sizeof(MSG_TYPE_UPDATE)-1)==0)
			{
				printf("sensor update: %s\n", msg.Message+sizeof(MSG_TYPE_UPDATE)-1);

				free(msg.Message);
				msg.Message = "sensor-update \"myval\" 12";
				msg.Size = strlen(msg.Message);
//#ifdef        _DEBUG_
				printf("write size = %d, Data size=%d\n", sizeof(msg.Size), msg.Size);
				printf("write size = %d, Data=%s\n", strlen(msg.Message), msg.Message);
//#endif        //_DEBUG_
				msg.Size = htonl(msg.Size);
				write(sock, &msg.Size, sizeof(msg.Size));
				write(sock, msg.Message, strlen(msg.Message));

			}
			else if(strncasecmp(msg.Message, MSG_TYPE_BROADCAST, sizeof(MSG_TYPE_BROADCAST)-1)==0)
			{
				printf("broadcast: %s\n",  msg.Message+sizeof(MSG_TYPE_BROADCAST)-1);

				free(msg.Message);
				msg.Message = "broadcast pablo";
				msg.Size = strlen(msg.Message);
//#ifdef	_DEBUG_
				printf("write size = %d, Data size=%d\n", sizeof(msg.Size), msg.Size);
				printf("write size = %d, Data=%s\n", strlen(msg.Message), msg.Message);
//#endif	//_DEBUG_ 
				msg.Size = htonl(msg.Size);
				write(sock, &msg.Size, sizeof(msg.Size));
				write(sock, msg.Message, strlen(msg.Message));
			}
			else
			{
				printf("unknow message type\n");
			}




		}

	}

	return 0;
}
