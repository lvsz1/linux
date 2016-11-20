#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFF_SIZE 30

void error_handling(char *message);

/**
基于TCP的半连接服务端
**/
int main(int argc ,char *argv[]){
    //客户端和服务端的socket描述符
    int  serv_sock;
    int clent_sock;
    //客户端和服务端的地址
    struct sockaddr_in serv_addr;
    struct sockaddr_in clent_addr;
    //客户端地址大小
    socklen_t  client_addr_size;
    //缓冲大小
    char buff[BUFF_SIZE] = "hello world!";
    //创建服务端saocket
    serv_sock = socket(AF_INET,SOCK_STREAM,0);
    //将server_addr中的内容清空
    memset(&serv_addr,0,sizeof(serv_addr));
    //初始化socket地址
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9990);

    //进行地址绑定
    if(bind(serv_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }
    //使服务端进入监听状态
    if(listen(serv_sock,5) == -1){
        error_handling("listen() error");
    }
    //获的客户端地址的大小
    client_addr_size = sizeof(clent_addr);
    clent_sock = accept(serv_sock,(struct sockaddr *) &clent_addr,&client_addr_size);

    int count = 2;
    while(count --){
        write(clent_sock,buff,BUFF_SIZE);
    }
    /**
    在数据输出完成之后，对输出流进行流半关闭
    这种状态下服务读不能向客户端写入数据，但是可以接受来自客户端的数据
    **/
    shutdown(clent_sock,SHUT_WR);
    //接受来自客户端的消息
    read(clent_sock,buff,BUFF_SIZE);
    //打印消息
    printf("Message from client : %s \n",buff);
    //彻底关闭TCP连接
    close(clent_sock);
    close(serv_sock);

return 0;

}



void error_handling(char * message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

