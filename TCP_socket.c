#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

void main(){
    struct sockaddr_in server,client;
    int sock,clientSocket;
    char receivedBytes[1024],sendBytes[1024];
    int bytes;

    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("Invalid Socket Descripter");
        exit(1);
    }
}
