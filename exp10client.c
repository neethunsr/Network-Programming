//Concurrent time server application using UDP
//Client side
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
    char buffer[100];
    char *message = "Concurrent Time Server Application runs successfully!\n";

    int clientSocket, n;
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (connect(clientSocket, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("[-]Error in connection.\n");
        exit(0);
    }

    sendto(clientSocket, message, 1000, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
    puts(buffer);

    close(clientSocket);
}
