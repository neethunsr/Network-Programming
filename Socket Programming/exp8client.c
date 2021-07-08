//Socket Programming:UDP
//Client Side

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char buffer[1000];
    char *message = "Hello from the client side!";
    int clientsocket, n;
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);
    servaddr.sin_family = AF_INET;

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (connect(clientsocket, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("\nError: Connection failed\n");
        exit(0);
    }

    int len = sizeof(servaddr);
    sendto(clientsocket, message, strlen(message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    n = recvfrom(clientsocket, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    close(clientsocket);
}