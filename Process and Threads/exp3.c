//Process and threads

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

const int n=3;

void *ThreadFunction(void *arg){
    printf("*Bon Jour!*\n");  //some random text
    sleep(1);
    printf("ThreadID: %d\t Process: %d\n",(void *)arg, getpid());
}

int main(){
    int i;
    pthread_t t;
    int j = fork();
    wait();
    if(j == 0){
        printf("Child Thread\n");
        for(i = 0; i < n; i++)
            pthread_create(&t, NULL, ThreadFunction, (void *)i);
    }
    else{
        printf("Parent Thread\n");
        for(i = 0; i < n; i++)
            pthread_create(&t, NULL, ThreadFunction, (void *)i);
    }

    pthread_exit(NULL);
    return 0;
}