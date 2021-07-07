//Shared Memory
//Writer Program
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

int main(){
    key_t key = ftok("shmfile", 65);
    int shmID = shmget(key, 1024, 0666 | IPC_CREAT);
    char * str = (char *)shmat(shmID, (void *)0, 0);

    printf("Write Data: ");
    scanf("%s", str);
    printf("Data written in memory: %s\n", str);
    shmdt(str);

    return 0;
}