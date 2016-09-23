#include"httpd.h"
void usage(char* proc)
{
	printf("usage: %s [PORT]\n",proc);
}
void not_found(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 404 NOT FOUND\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>NOT FOUND</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>file is not exist</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void bad_request(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 400 BAD REQUEST\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>BAD REQUEST</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>the request is error</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void method_not_allowed(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 405 METHOD NOT ALLOWED\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>METHOD NOT ALLOWED</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>request method is not be allowed</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void server_error(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 500 SERVER ERROR\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>SERVER ERROR</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>server has error</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void server_unavailable(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 503 SERVER UNAVAILABLE\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>SERVER UNAVAILABLE</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>server is unavailable</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void default_error(int client)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.0 DEFAULT ERROR\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"Content-type:text/html\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<htm><title>DEFAULT ERROR</title>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"<body><p>this is default error</p></body>\r\n");
	send(client,buf,strlen(buf),0);
	sprintf(buf,"</html>\r\n");
	send(client,buf,strlen(buf),0);
}
void return_errno_client(int client,int status_code)
{
	switch(status_code){
		case 404://not found
			not_found(client);
			break;
		case 400://bad request
			bad_request(client);
			break;
		case 405://method not allowed
			method_not_allowed(client);
			break;
		case 500://server error
			server_error(client);
			break;
		case 503://server unavailable
			server_unavailable(client);
			break;
		default:
			default_error(client);
			break;
	}
}
int get_line(int client,char buf[],int size)
{
	if(!buf || size<0){
		return -1;
	}
	int i=0;
	char c='\0';
	int n=0;
	while((i<size-1) && (c!='\n')){
		n=recv(client,&c,1,0);
		if(n>0){
			if(c=='\r'){
				n=recv(client,&c,1,MSG_PEEK);
				if(n>0 && c=='\n'){
					n=recv(client,&c,1,0);
				}else{
					c='\n';
				}
			}
			buf[i++]=c;
		}else{
			c='\n';
		}
	}
	buf[i]='\0';
	return i;
}
int startup(unsigned short port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		printf("%d : %s\n",errno,strerror(errno));
		exit(1);
	}
	//reuse port
	int flag=1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){
		printf("%d : %s\n",errno,strerror(errno));
		exit(1);
	}
	if(listen(sock,_BACK_LOG_)<0){
		printf("%d : %s\n",errno,strerror(errno));
		exit(1);
	}
	return sock;

}
void clear_header(int client)
{
	char buf[_BLOCK_SIZE_];
	int ret=-1;
	memset(buf,'\0',sizeof(buf));
	do{
		ret=get_line(client,buf,sizeof(buf)-1);
	}while(ret>0 && strcmp(buf,"\n")!=0);
}
void echo_html(int client,char* path,size_t size)
{
	if(!path){
		return;
	}
	clear_header(client);
	int fd=open(path,O_RDONLY,0);
	if(fd<0){
		return_errno_client(client,404);
		return;
	}else{
		char buf[_BLOCK_SIZE_];
		memset(buf,'\0',sizeof(buf));
		sprintf(buf,"HTTP/1.0 200 OK\r\n\r\n");
		send(client,buf,strlen(buf),0);
		sendfile(client,fd,NULL,size);
	}
	close(fd);
}
void exe_cgi(int client, char* path, char* method, char* query_string)
{
	int cgi_input[2]={0,0};
	int cgi_output[2]={0,0};
	pid_t id;
	int numchars=-1;
	char buf[_BLOCK_SIZE_];
	int content_length=-1;
	if(strcasecmp(method,"GET")==0){//CGI && GET
		clear_header(client);
	}else{//CGI && POST
		//content-length: 12345
		do{
			memset(buf,'\0',sizeof(buf));
			numchars=get_line(client,buf,sizeof(buf));
			if(strncasecmp(buf,"Content-Length:",strlen("Content-Length:"))==0){
				content_length=atoi(&buf[16]);
			}
		}while(numchars>0 && strcmp("\n",buf));
		if(content_length==-1){
			return_errno_client(client,404);
			return;
		}
	}
	sprintf(buf,"HTTP/1.0 200 OK\r\n\r\n");
	send(client,buf,strlen(buf),0);
	if(pipe(cgi_input)<0){
		perror("pipe input");
		return;
	}
	if(pipe(cgi_output)<0){
		close(cgi_input[0]);
		close(cgi_input[1]);
		perror("pipe output");
		return;
	}
	if((id=fork())<0){
		close(cgi_input[0]);
		close(cgi_input[1]);
		close(cgi_output[0]);
		close(cgi_output[1]);
		return_errno_client(client,404);
		return;
	}else if(id==0){//child
		char meth_env[_BLOCK_SIZE_/10];
		char query_env[_BLOCK_SIZE_];
		char content_len_env[_BLOCK_SIZE_/5];
		memset(meth_env,'\0',sizeof(meth_env));
		memset(query_env,'\0',sizeof(query_env));
		memset(content_len_env,'\0',sizeof(content_len_env));

		close(cgi_input[1]);
		close(cgi_output[0]);
		//0->input[0]
		dup2(cgi_input[0],0);
		//1->output[1]
		dup2(cgi_output[1],1);
		sprintf(meth_env,"REQUEST_METHOD=%s",method);
		putenv(meth_env);
		printf("method=%s\n",getenv("REQUEST_METHOD"));
		if(strcasecmp(method,"GET")==0){//GET
			sprintf(query_env,"QUERY_STRING=%s",query_string);
			putenv(query_env);
			//printf("%s\n",query_string);
		}else{//POST
			sprintf(content_len_env,"CONTENT_LENGTH=%d",content_length);
			putenv(content_len_env);
		}
		execl(path,path,NULL);
		exit(1);
	}else{//father
		close(cgi_input[0]);
		close(cgi_output[1]);
		char ch;
		int i=0;
		if(strcasecmp(method,"POST")==0){
			for(;i<content_length;++i){
				recv(client,&ch,1,0);
				write(cgi_input[1],&ch,1);
			}
		}
		while(read(cgi_output[0],&ch,1)>0){
			send(client,&ch,1,0);
		}
		close(cgi_input[1]);
		close(cgi_output[0]);
		waitpid(id,NULL,0);
	}
}
void* accept_request(void* arg)
{
	printf("get a new connect...\n");
	pthread_detach(pthread_self());//set the thread to separate status,do not to join
	int cgi=0;
	char method[_BLOCK_SIZE_%10];//save the request mathod
	char url[_BLOCK_SIZE_];//save the request resouce
	char* query_string=NULL;//point to GET mathod parameter
	int client=(int)arg;
	//save request line
	char buf[_BLOCK_SIZE_];
	char path[_BLOCK_SIZE_];
	memset(buf,'\0',sizeof(buf));
	memset(method,'\0',sizeof(method));
	memset(url,'\0',sizeof(url));
	memset(path,'\0',sizeof(path));
#ifdef _DEBUG_
	printf("in debug mode...\n");
	while(get_line(client,buf,sizeof(buf))>0){
		printf("%s",buf);
		fflush(stdout);
	}
	printf("\n");
#endif
	if(get_line(client,buf,sizeof(buf))<0){
		return_errno_client(client,404);
		close(client);
		return (void*)-1;
	}
	int i=0;
	int j=0;
	//get the request method
	while(!isspace(buf[j]) && i<sizeof(method)-1 && j<sizeof(buf)){
		method[i]=buf[j];
		++i;
		++j;
	}
	//if the mathod is not GET or POST
	if(strcasecmp(method,"GET") && strcasecmp(method,"POST")){
		return_errno_client(client,404);
		close(client);
		return (void*)-1;
	}
	//the mathod is POST
	if(strcasecmp(method,"POST")==0){
		cgi=1;
	}
	//skip space
	while(isspace(buf[j]) && j<sizeof(buf)){
		j++;
	}
	i=0;
	//get url
	while(!isspace(buf[j]) && i<sizeof(url)-1 && j<sizeof(buf)){
		url[i]=buf[j];
		i++;
		j++;
	}
	//the method is GET
	if(strcasecmp(method,"GET")==0){
		query_string=url;
		while(*query_string!='?' && *query_string!='\0'){
			query_string++;
		}
		//GET mathod has the parameters 
		if(*query_string=='?'){
			*query_string='\0';
			query_string++;
			cgi=1;
		}
	}
	sprintf(path,"htdocs%s",url);
	if(path[strlen(path)-1]=='/'){
		strcat(path,MAIN_PAGE);
	}
	struct stat st;
	if(stat(path,&st)<0){//request file is not exist
		return_errno_client(client,404);
		close(client);
		return (void*)-1;
	}else{
		if(S_ISDIR(st.st_mode)){//S_ISDIR : whether the directory file
			strcat(path,"/");
			strcat(path,MAIN_PAGE);
		}else if((st.st_mode & S_IXUSR)||(st.st_mode & S_IXGRP)||(st.st_mode & S_IXOTH)){//whether it has execttable power
			cgi=1;
		}else{
		}
		if(cgi){
			exe_cgi(client,path,method,query_string);
		}else{
			echo_html(client,path,st.st_size);
		}
	}
	close(client);
	return NULL;
}
int main(int argc,char* argv[])
{
	if(argc!=2){
		usage(argv[0]);
		exit(1);
	}
	unsigned short port=atoi(argv[1]);
	struct sockaddr_in client;
	int len=0;
	int listen_sock=startup(port);
	while(1){
		int new_sock=accept(listen_sock,(struct sockaddr*)&client,&len);
		if(new_sock<0){
			perror("accept");
			continue;
		}
		//printf("get a new connect...\n");
		pthread_t id;
		pthread_create(&id,NULL,accept_request,(void*)new_sock);
		//pthread_detach(id);
	}
	close(listen_sock);
	return 0;
}
