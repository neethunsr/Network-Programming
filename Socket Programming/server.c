/*
Implement a TCP/UDP client and server, Your TCP or UDP client/server will communicate
over the network and exchange data. 

The server will start in passive mode listening on a specified port for a transmission
from a client. 

Separately, the client will be started and will contact the server. 

The client will pass the server a Square Matrix of size N*N.

Server will print it in spiral order and send to client and the client will print the same.
*/

//Server Side

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int s, newSocket;
    int spiralMatrix[100], matrix[10][10], N, array[100];

    struct sockaddr_in server;
    socklen_t addr_size;

    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(7891);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(s, (struct sockaddr*)&server, sizeof(server));

    if (listen(s, 5 ) == 0)
        printf("Listening for the client to be live..\n");
    else
        printf("Error\n");

    addr_size = sizeof server;
    newSocket = accept(s, (struct sockaddr*)&server, &addr_size);

    recv(newSocket, &N, sizeof(N), 0);
    recv(newSocket, &array, sizeof(matrix), 0);

    //convert the 1d array input to matrix
    int k=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            matrix[i][j] = array[k];
            k++;
        }
    }

    //create spiral matrix
    int i, j, c=0;
    for(i=N-1,j=0; i>0; i--,j++){
        for(k=j; k<i; k++){
            spiralMatrix[c]=matrix[j][k];
            c++;
        }
        for(k=j; k<i; k++){
            spiralMatrix[c]=matrix[k][i];
            c++;
        } 
        for(k=i; k>j; k--){
            spiralMatrix[c]=matrix[i][k];
            c++;
        }
        for(k=i; k>j; k--){
            spiralMatrix[c]=matrix[k][j];
            c++;
        } 
        int middle = (N-1)/2;
        if(N%2 == 1){
            spiralMatrix[c]=matrix[middle][middle];
        }
    }
    printf("Spiral Matrix: ");
    for(int i=0; i<N*N; i++)
        printf("%d ", spiralMatrix[i]);
    printf("\n");

    send(newSocket, &spiralMatrix, sizeof(spiralMatrix), 0);

    return 0;
}