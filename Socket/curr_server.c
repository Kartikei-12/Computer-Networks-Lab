#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int __random__(int max)
{
	srand(time(NULL));
	return (rand() % max) + 1;
}

int main()
{
    time_t clock;
	char dataSending[1025];
	
	// client socket descriptor
	int clintConnt = 0, replyCount = 0;

	struct sockaddr_in ipOfServer;
	
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	memset(dataSending, '0', sizeof(dataSending));
	
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	//									^ LocalHost
	ipOfServer.sin_port = htons(2017);

	// Socket creation
	// AF_INET IPv4
	// AF_INET6 IPv6
	// SOCK_STREAM: TCP
	// SOCK_DGRAM: UDP
	// 0: Internt Protocol version 
	int clientListen = socket(AF_INET, SOCK_STREAM, 0);
	
	
	// clientListen: Socket to bind
	// (struct sockaddr*)&ipOfServer: Bind to this address
	// sizeof(ipOfServer): Length of address
	bind(
		clientListen,
		(struct sockaddr*)&ipOfServer,
		sizeof(ipOfServer)
	);
	listen(clientListen , 10); // Number of client request in queue
 

	while(1)
	{
		printf("\nServer listening.\n");
		
		// clientListen: From request on socket
		// Accept from socket address
		clintConnt = accept(clientListen, (struct sockaddr*)NULL, NULL);
		pid_t pp = fork();
		if(clintConnt > 0 && pp == 0)
		{
			printf("\n********************* Response ************************\n");
			printf("clintConnt: %d\n", clintConnt);
			clock = time(NULL);
			snprintf(
				dataSending,
				sizeof(dataSending),
				"%.24s\r\n",
				ctime(&clock)
			);
			
			// Write to given socket dataSending of length strlen(dataSending)
			write(clintConnt, dataSending, strlen(dataSending));
	
			int sl = __random__(5);
			printf("Sleeping for %d with reply count %d\n", sl, replyCount);
			printf("\n********************* Response Done************************\n");
			sleep(sl);
			close(clintConnt);
			exit(1);
		}
		++replyCount;
		printf("Reply count: %d\n", replyCount);
		printf("\nIteration done\n");
		sleep(1);
	} 
    return 0;
}