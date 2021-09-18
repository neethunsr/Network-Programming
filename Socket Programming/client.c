/*
Implement a TCP/UDP client and server, Your TCP or UDP client/server will communicate
over the network and exchange data. 

The server will start in passive mode listening on a specified port for a transmission
from a client. 

Separately, the client will be started and will contact the server. 

The client will pass the server a Square Matrix of size N*N.

Server will print it in spiral order and send to client and the client will print the same.
*/

//Client Side

#include<stdio.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
    int s, N, matrix[50][50], spiralMatrix[100], array[100];
    struct sockaddr_in client;
    socklen_t addr_size;

    //Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(7891);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_size = sizeof client;
    connect(s, (struct sockaddr*)&client, addr_size);

    printf("Enter the order of matrix: ");
    scanf("%d", &N);
    send(s, &N, sizeof(N), 0);

    printf("Enter the matrix:\n");
    for(int i=0; i<N*N; i++){
        scanf("%d", &array[i]);
    }

    send(s, &array, sizeof(array), 0);

    recv(s, spiralMatrix, sizeof(spiralMatrix), 0);

    printf("The Spiral Matrix is: ");
    for(int i=0; i<N*N; i++){
        printf("%d ", spiralMatrix[i]);
    }
    printf("\n");
    return 0;
}