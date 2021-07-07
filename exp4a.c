//Ordinary pipes

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define size 16

char* msgA = "Message A";
char* msgB = "Message B";
char* msgC = "Message C";

int main(){
    char inbuf[size];
    int p[2], i;
    
    if(pipe(p) < 0)
        exit(1);
    write(p[1], msgA, size);
    write(p[1], msgB, size);
    write(p[1], msgC, size);
    for(i = 0; i < 3; i++){
        read(p[0], inbuf, size);
        printf("%s\n", inbuf);
    }
    return 0;
}