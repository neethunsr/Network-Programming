//First Readers-Writers Problem

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

pthread_mutex_t mutex, res;
pthread_t tid;
int readcount = 0;

void *reader(void *var){
    setbuf(stdout, NULL);
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        pthread_mutex_lock(&res);\
    printf("Reader %d is inside\n", var);
    pthread_mutex_unlock(&mutex);
    sleep(2);
    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount == 0)
        pthread_mutex_unlock(&res);
    pthread_mutex_unlock(&mutex);
    printf("Reader is leaving...\n");
    pthread_exit(NULL);
}

void *writer(void *var){
    setbuf(stdout, NULL);
    pthread_mutex_lock(&res);
    printf("Writer has entered\n");
    sleep(2);
    printf("Writer is leaving...\n");
    fflush(stdout);
    pthread_mutex_unlock(&res);
    pthread_exit(NULL);
}

int main(){
    setbuf(stdout, NULL);
    int n1, n2, i, j;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&res, NULL);
    srand(time(NULL));
    for(i=0; i<10; i++){
        j = rand();
        if(j%2 == 1)
            pthread_create(&tid, NULL, reader, (void *)i);
        else
            pthread_create(&tid, NULL, writer, NULL);
    }
    pthread_exit(NULL);
}