#include"demo_client.h"
//void usage(const char* proc)
//{
//	printf("Usage:%s [IP] [PORT]\n",proc);
//}
//int main()
//{
//	if(argc!=3){
//		usage(argv[0]);
//		exit(1);
//	}
//	const char* ip=argv[1];
//	int sock=socket(AF_INET,SOCK_STREAM,0);
//	if(sock==-1){
//		printf("%d : %s\n",errno,strerror(errno));
//		exit(1);
//	}
//	unsigned short port=atoi(argv[2]);
//	struct sockaddr_in remote;
//	remote.sin_family=AF_INET;
//	remote.sin_port=htons(port);
//	remote.sin_addr.s_addr=inet_addr(argv[1]);
//	int ret=connect(sock,(struct sockaddr*)&remote,sizeof(remote));
//	if(ret<0){
//		perror("connect");
//		exit(1);
//	}
//	char buf[1024];
//	memset(buf,'\0',sizeof(buf));
//	while(1){
//		size_t ret=recv(sock,buf,sizeof(buf)-1,0);
//		if(ret<0){
//			perror("recv");
//			break;
//		}
//		buf[ret]='\0';
//		printf("%s",buf);
//		memset(buf,'\0',sizeof(buf));
//	}
//	printf("\n");
//	close(sock);
//	return 0;
//}
int main()
{
	return 0;
}
