//Concurrent File Server
//Server side

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#define PORT 8080

void Sender(int socket, char *filename)
{
    struct stat obj;
    int file, filesize;
    stat(filename, &obj);
    file = open(filename, O_RDONLY);
    filesize = obj.st_size;

    send(socket, &filesize, sizeof(int), 0);
    sendfile(socket, file, NULL, filesize);
    printf("File sent to the client!\n");
}

void *callBack(void *socket)
{
    int socketfd = *(int *)socket;
    char serverResponse[BUFSIZ], filename[BUFSIZ];
    recv(socketfd, filename, BUFSIZ, 0);
    //If the file exists, notify the client and send it
    if (access(filename, F_OK) != -1)
    {
        snprintf(serverResponse, 10, "%d", getpid());
        write(socketfd, serverResponse, 10);
        Sender(socketfd, filename);
    }
    else
    {
        strcpy(serverResponse, "NO");
        write(socketfd, serverResponse, strlen(serverResponse));
    }
    free(socket);
}

int main(int argc, char **argv)
{
    int socketServer, socketClient, *newSocket, len = sizeof(struct sockaddr_in);
    struct sockaddr_in server, client;

    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1)
    {
        printf("SOCKET NOT CREATED");
        exit(0);
    }
    printf("Socket created successfully!\n");

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (bind(socketServer, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("BIND FAILED");
        exit(0);
    }
    printf("Binding successful!\n");
    listen(socketServer, 3);
    printf("Listening for incoming connections!\n");

    while (socketClient = accept(socketServer, (struct sockaddr *)&client, (socklen_t *)&len))
    {
        printf("Client connected!\n");
        pthread_t sniffer;
        newSocket = malloc(1);
        *newSocket = socketClient;
        pthread_create(&sniffer, NULL, callBack, (void *)newSocket);
        pthread_join(sniffer, NULL);
    }

    if (socketClient < 0)
    {
        printf("Accept failed!\n");
        return 1;
    }
    return 0;
}