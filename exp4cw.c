//Message Queue
//Writer program
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
    msg.msgType = 1;

    printf("Write Data: ");
    scanf("%s",msg.msgText);
    msgsnd(msgID, &msg, sizeof(msg), 0);

    printf("Data sent is: %s\n", msg.msgText);
    return 0;
}
