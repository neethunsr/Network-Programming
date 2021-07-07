//Second Readers-Writers Problem

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

pthread_mutex_t rmutex, wmutex, res, readTry;
pthread_t tid;
int readcount = 0, writecount = 0;

void *reader(void *var){
    setbuf(stdout, NULL);
    pthread_mutex_lock(&readTry);
    pthread_mutex_lock(&rmutex);
    readcount++;
    if(readcount == 1)
        pthread_mutex_lock(&res);
    printf("Reader %d is reading...\n",var);
    pthread_mutex_unlock(&rmutex);
    pthread_mutex_unlock(&readTry);
    sleep(2);
    pthread_mutex_lock(&rmutex);
    readcount--;
    printf("Reader %d is leaving...\n", var);
    if(readcount == 0)
        pthread_mutex_unlock(&res);
    pthread_mutex_unlock(&rmutex);
}

void *writer(void *var){
    setbuf(stdout, NULL);
    pthread_mutex_lock(&wmutex);
    writecount++;
    printf("Writer %d is reading...\n", var);
    if(writecount == 1)
        pthread_mutex_lock(&readTry);
    pthread_mutex_unlock(&wmutex);
    pthread_mutex_lock(&res);
    sleep(2);
    pthread_mutex_unlock(&res);
    pthread_mutex_lock(&wmutex);
    writecount--;
    printf("Writer %d is leaving...\n", var);
    if(writecount == 0)
        pthread_mutex_unlock(&readTry);
    pthread_mutex_unlock(&wmutex);
    pthread_exit(NULL);
}

int main(){
    setbuf(stdout, NULL);
    int n1, n2, i, j;
    pthread_mutex_init(&rmutex, NULL);
    pthread_mutex_init(&wmutex, NULL);
    pthread_mutex_init(&res,NULL);
    srand(time(NULL));
    for(i=0; i<10; i++){
        j = rand();
        if(j%2 == 1)
            pthread_create(&tid, NULL, reader, (void *)i);
        else
            pthread_create(&tid, NULL, writer, (void *)i);
    }
    pthread_exit(NULL);
}