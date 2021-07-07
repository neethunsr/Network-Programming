//Messaged Queue
//Reader Program
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
    long msgType;
    char msgText[100];
}msg;

int main(){
    key_t key;
    int msgID;

    key = ftok("pgmfile", 65);
    msgID = msgget(key, 0666 | IPC_CREAT);
    
    msgrcv(msgID, &msg, sizeof(msg), 1, 0);

    printf("Data received is: %s\n", msg.msgText);
    msgctl(msgID, IPC_RMID, NULL);
    
    return 0;
}