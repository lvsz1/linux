#include <iostream>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct buf
{
    int  order;
    unsigned char data[8000];
    int  add;
};

int main()
{
    int sockfd;
    int r;
    int on = 1;
    struct sockaddr_in saddr;
    struct buf buf;

    sockfd =  socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("219.216.87.33");
    saddr.sin_port = htons(9999);

    buf.order = 1;
    strcpy((char*)buf.data, "Hello world ni hao");
    buf.add = 2;

    int optval = 3000;
    int len1 = 4;
    getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, (socklen_t *)&len1);
    cout << "recvbuf: " << optval << endl;

    r = sendto(sockfd, &buf, sizeof(buf), 0,
               (struct sockaddr*)&saddr, sizeof(saddr));
    if (r == -1)
    {
        perror("sendto error");
        exit(-1);
    }
    cout << "finish" << endl;
    return 0;
}

