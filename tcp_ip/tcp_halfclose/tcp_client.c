#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFF_SIZE 30

void error_handling(char *message);


int main(int argc ,char *argv[]){
    int sock;

    char buff[BUFF_SIZE];
    int read_count;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET,SOCK_STREAM,0);

    memset(&server_addr,0,sizeof(server_addr));

    //初始化socket地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.2");
    server_addr.sin_port = htons(9990);

    connect(sock,(struct sockaddr *) &server_addr,sizeof(server_addr));

    while(read_count = read(sock,buff,BUFF_SIZE) != 0){
        printf("%s\n", buff);
    }
    //打印接收到的数据
    puts("Recevied file data");
    //接收完成之后向服务端发送一个消息
    write(sock,"Thank you ",10);

    close(sock);
    return 0;
}

void error_handling(char * message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

