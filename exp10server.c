#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 4444

int main()
{
    time_t t;
    time(&t);
    char buffer[100];
    char *message = ctime(&t);

    int serverSocket, len;
    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(serverSocket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
    int n = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);

    buffer[n] = '\0';
    puts(buffer);

    sendto(serverSocket, message, 1000, 0, (struct sockaddr *)&cliaddr, len);
}
