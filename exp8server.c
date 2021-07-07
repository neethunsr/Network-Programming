//Socket Programming:UDP
//Server Side

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>

int main(){
    char buffer[1000];
    char *message = "Hello from the server side!";
    int serversocket, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8080);
    servaddr.sin_family = AF_INET;

    bind(serversocket, (struct sockaddr*)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
    int n = recvfrom(serversocket, (char *)buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);

    buffer[n] = '\0';
    printf("%s\n", buffer);

    sendto(serversocket, message, strlen(message), 0, (struct sockaddr*)&cliaddr, len);
    return 0;
}