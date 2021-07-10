//Concurrent File Server
//Client side

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

int main()
{
    int socketServer;
    struct sockaddr_in server;
    char requestMessage[BUFSIZ], replyMessage[BUFSIZ];

    int filesize, file;
    char *data, filename[20], storageFile[20];

    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1)
    {
        perror("SOCKET NOT CREATED");
        return 1;
    }
    printf("Socket created successfully!\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(socketServer, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed...");
        return 1;
    }
    printf("Connection successful!\n");

    printf("Enter the name of file to search: ");
    scanf("%s", filename);

    write(socketServer, filename, strlen(filename));
    recv(socketServer, replyMessage, 10, 0);
    int pid = atoi(replyMessage);
    printf("Process ID: %d\n", pid);
    if (pid > 0)
    {
        printf("File found!!\n");
        printf("Enter the name of the file to store data: ");
        scanf("%s", storageFile);

        recv(socketServer, &filesize, sizeof(int), 0);
        data = malloc(filesize);
        file = open(storageFile, O_CREAT | O_EXCL | O_WRONLY, 0666);
        recv(socketServer, data, filesize, 0);
        write(file, data, filesize);

        printf("File copied!\n");
        close(file);
    }
    else if (strcmp(replyMessage, "NO") == 0)
    {
        fprintf(stderr, "File not found!\n");
    }
    return 0;
}