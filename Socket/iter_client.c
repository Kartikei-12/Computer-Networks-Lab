#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main()
{
    int n = 0;
    char dataReceived[1024];
    
    struct sockaddr_in ipOfServer;
 
    memset(dataReceived, '0' ,sizeof(dataReceived));

    // Setting internet socket address
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(2017);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    for(int i=0; i<5; ++i) {

        // Socket creation
        // AF_INET IPv4
        // AF_INET6 IPv6
        // SOCK_STREAM: TCP
        // SOCK_DGRAM: UDP
        // 0: Internt Protocol, protocol value 
        int ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(ClientSocket < 0)
        {
            printf("Socket not created \n");
            return 1;
        }

        // connect socket ClientSocket
        // to socket on address (struct sockaddr *)&ipOfServer
        // of address length
        int connectStatus = connect(
            ClientSocket,
            (struct sockaddr *)&ipOfServer,
            sizeof(ipOfServer)
        );
        if(connectStatus < 0)
        {
            printf("Connection failed due to port and ip problems\n");
            return 1;
        }

        // Read on socket, data in dataReceived, sizeof(dataReceived)-1 bytes  
        // n: Number of bytes recieved
        n = read(ClientSocket, dataReceived, sizeof(dataReceived)-1);
        dataReceived[n] = 0;
        if(fputs(dataReceived, stdout) == EOF)
            printf("\nStandard output error");
        printf("\n--\n");
            
        if( n < 0)
            printf("Standard input error \n");
        printf("\n%d Request done\n", i+1);
    }
    return 0;
}