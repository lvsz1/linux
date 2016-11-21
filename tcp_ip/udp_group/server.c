#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <ctype.h>
#include <net/if.h>

#define SERVER_PORT 5555 
#define CLIENT_PORT 5556 
#define MAXLINE 1024 
#define GROUP "239.0.0.2"

int main(void)
{
	int sockfd,i;
	ssize_t len;
	struct sockaddr_in serveraddr,clientaddr;
	char buf[MAXLINE];
	char ipstr[INET_ADDRSTRLEN];//16个字节
	socklen_t clientlen;
	struct ip_mreqn group;//设置组播

	//构造用于UDP通信的套接字
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family =AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons(SERVER_PORT);
	//printf("%x\n",INADDR_ANY);
	bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	/*设置组地址*/
	inet_pton(AF_INET,GROUP,&group.imr_multiaddr);
	/*设置本地地址*/
	inet_pton(AF_INET,"0.0.0.0",&group.imr_address);
	group.imr_ifindex=if_nametoindex("eth0");//将网卡名转换成序号 等价 ip ad

	setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_IF,&group,sizeof(group));
	/*构造client地址 IP+端口*/
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family=AF_INET;
	inet_pton(AF_INET,GROUP,&clientaddr.sin_addr.s_addr);
	clientaddr.sin_port=htons(CLIENT_PORT);
	while(1){	
	fgets(buf,sizeof(buf),stdin);	
	sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
	}
	close(sockfd);
	return 0;
}

