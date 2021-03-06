#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define MAX 2000
#define PORT 43454
#define SA struct sockaddr 

void func(int sockfd)
{
   char buff[MAX];
   int n;
   for(;;)
   {
	bzero(buff,sizeof(buff));
	printf("Enter the string : "); //9. type the message
	n=0;

   while((buff[n++]=getchar())!='\n'); //12. while loop will work for chat process
	write(sockfd,buff,sizeof(buff));
	bzero(buff,sizeof(buff));
	read(sockfd,buff,sizeof(buff));
	printf("From Server : %s",buff); //11. got a reply from server.

    if((strncmp(buff,"exit",4))==0) //13. if client type exit the code will stop exchanging messages from there on
    {
	printf("Client Exit...\n");
	break;
    }
   }
}

int main()
{
   int sockfd,connfd;
   struct sockaddr_in servaddr,cli;
   sockfd=socket(AF_INET,SOCK_STREAM,0); //5. socket created 

   if(sockfd==-1)
   {
	printf("socket creation failed...\n");
	exit(0);
   }

   else
	printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));
        
        //6. Initialize the server address by the port and IP
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);
   
   // 7. send connection request to the server
   if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
   {
	printf("connection with the server failed...\n");
	exit(0);
   }
   
   else
	printf("connected to the server..\n");
	func(sockfd);
	close(sockfd);
}
