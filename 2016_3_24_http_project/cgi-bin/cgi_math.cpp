#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<string>
using namespace std;
void my_math(string _data)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	strncpy(buf,_data.c_str(),_data.size());
	char* curr=buf;
	char* data1=NULL;
	char* data2=NULL;
	while(*curr!='\0'){
		if(*curr=='='){
			if(data1==NULL){
				data1=++curr;
			}else{
				data2=++curr;
			}
			continue;
		}
		if(*curr=='&'){
			*curr=='\0';
		}
		++curr;
	}
	int d1=atoi(data1);
	int d2=atoi(data2);
	int add = d1 + d2;
	int sub = d1 - d2;
	int mul = d1 * d2;
	int div = d1 / d2;
	int mod = d1 % d2;
	cout<<"<html>"<<endl;
	cout<<"<head>"<<endl;
	cout<<"</head>"<<endl;
	cout<<"<body>"<<endl;
	cout<<"<h1>"<<"data1"<<" + "<<"data2 = "<<add<<"</h1>"<<endl;
	cout<<"<h1>"<<"data1"<<" - "<<"data2 = "<<sub<<"</h1>"<<endl;
	cout<<"<h1>"<<"data1"<<" * "<<"data2 = "<<mul<<"</h1>"<<endl;
	cout<<"<h1>"<<"data1"<<" / "<<"data2 = "<<div<<"</h1>"<<endl;
	cout<<"<h1>"<<"data1"<<" % "<<"data2 = "<<mod<<"</h1>"<<endl;
	cout<<"</body>"<<endl;
	cout<<"</html>"<<endl;
}
int main()
{
	string method;
	string query_string;
	string content_length;
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	if(getenv("REQUEST_METHOD")==NULL){
		exit(1);
	}
	method=getenv("REQUEST_METHOD");
	cout<<method<<endl;
	if(strcasecmp(method.c_str(),"GET")==0){
		if(getenv("QUERY_STRING")==NULL){
			exit(1);
		}
		query_string=getenv("QUERY_STRING");
		//cout<<query_string<<endl;
		//my_math("data1=1&data2=2");
		my_math(query_string);
		//cout<<query_string<<endl;
	}else if(strcasecmp(method.c_str(),"POST")==0){
		if(getenv("CONTENT_LENGTH")==NULL){
			exit(1);
		}
		content_length=getenv("CONTENT_LENGTH");
		cout<<content_length<<endl;
		int len=atoi(content_length.c_str());
		int i=0;
		for(;i<len;i++){
			read(0,&buf[i],1);
		}
		my_math(buf);
	}else{
		exit(1);
	}
	return 0;
}
