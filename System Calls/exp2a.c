//C program to illustrate I/O System Calls - Process Control

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int x = fork();
    wait();
    printf("Fork Value : %d\t pid : %d\n",x,getpid());
    exit(0);

    printf("Hello World!");
    return 0;
}   