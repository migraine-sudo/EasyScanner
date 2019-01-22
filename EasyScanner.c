//gcc -o EasyScanner EasyScanner.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> //系统调用
/*socket调用*/
#include<netinet/in.h>
#include<arpa/inet.h>

void StartUI()
{
	/*启动部分UI*/
	/*简介：模拟一些程序的加载界面，注意usleep函数与printf配合，需要加一个fflush(stdout)，否则printf的数据不会及时输出*/
	int i=0;
	
	usleep(500000);//暂停0.5秒
	fflush(stdout);//清空缓冲区，否则printf将等到sleep全部结束才会被打印出来	
	printf(".");
	usleep(500000);
	fflush(stdout);
	printf(".");
	usleep(500000);
	fflush(stdout);
      	  printf(".");
	while(i<5)
	{
		fflush(stdout);
		printf("\b\b\b.  ");//退格符号，删除之前的"...",改为".  "(注意为了完全覆盖之前的三个点，输出一个点需要加两个空格，两个点需要加一个空格。具体参考\b的性质)
		usleep(500000);
		fflush(stdout);
		printf("\b\b\b.. ");
		usleep(500000);
		fflush(stdout);	
		printf("\b\b\b...");
		usleep(500000);
		i++;
	}
	printf("\n");
}



/*扫描这个IP的所有端口*/
void scanport(char* target)
{
	printf("invoking allports scan part");
	//StartUI();
	/*扫描模块*/
	
	int sockfd;
	struct sockaddr_in servaddr;
	int ports_up=0;
	for(int i=0;i<65535;i++)
	{	
		/*#include<string.h>*/
		bzero(&servaddr,sizeof(servaddr));
		
		sockfd=socket(AF_INET,SOCK_STREAM,0);
		servaddr.sin_family=AF_INET;
		servaddr.sin_port=htons(i);
		servaddr.sin_addr.s_addr=inet_addr(target);
		if(inet_addr(target)==-1){
		printf("inet_addr Error");}
		/*#include<netinet/in.h>*/
		//if(inet_pton(AF_INET,target,&servaddr.sin_addr)<=0)
		//{printf("inet_pton Error");}
		int ifportused=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
		if(ifportused<0)
		{ 	
			//printf("useless port:%d\n",i);
			close(sockfd);
			continue;
		}
		else{
			printf("useful port:%d\n",i);
			close(sockfd);
			ports_up++;
			continue;
		}
		
	}
	printf("\nscan complete(scan 65535 ports, %d ports up\n",ports_up);
	
}

int main(int argc,char **argv)
{
	
	/*指令模块*/
	if(!strcmp(argv[1],"-h"))
	{
		printf("help list:\n");
		printf("use'./EasyScanner+tragetIP'to scan all the ports\n");
		printf("use'./EasyScanner+IP+port1+port2'to scan prot1 to port 2\n");
		argc=0;
	}
	
	/*如果输入参数数量（atgc）为2（包括程序名称），扫描这个IP的所有端口*/
	if(argc==2)
	scanport(argv[1]);/*将第二个参数传入函数（注意:argv是字符串格式）*/
	
	printf("\nuse -h to get more information!\n");
	
}

