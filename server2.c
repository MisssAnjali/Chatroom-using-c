#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2000       //max length of buffer
#define PORT 43454  
#define SA struct sockaddr 

void func(int sockfd)
{
   char buff[MAX];
   int n;
   for(;;)
   {
      bzero(buff,MAX);
      read(sockfd,buff,sizeof(buff));
      printclf("From client: %s\t To client : ",buff); //10. got a msg from client, replies the message.
      bzero(buff,MAX);
      n=0;
          while((buff[n++]=getchar())!='\n'); //12. while loop will work for chat process
          write(sockfd,buff,sizeof(buff));

	  //13. if clients type exit the code will stop exchanging messages from there on
          if(strncmp("exit",buff,4)==0)
		{
		  printf("Server Exit...\n");
		  break;
		}
    }
}

int main()
{
   int sockfd,connfd,len;
   struct sockaddr_in servaddr,cli;
   sockfd=socket(AF_INET,SOCK_STREAM,0); //1. creating a socket
   if(sockfd==-1)
   {
	printf("socket creation failed...\n");
	exit(0);
   }

   else
	printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));

        //2. Initialize the server address by the port and IP:
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
   
   // 3. Bind to the set port and IP:
   if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
   {
	printf("socket bind failed...\n");
	exit(0);
   }
   else
	printf("Socket successfully binded..\n");

   // 4. Listen for clients:
   if((listen(sockfd,5))!=0)
   {
	printf("Listen failed...\n");
	exit(0);
   }
  
   else
	printf("Server listening..\n");

        // 8. Accept an incoming connection:
	len=sizeof(cli);
	connfd=accept(sockfd,(SA *)&cli,&len);

   if(connfd<0)
   {
	printf("server acccept failed...\n");
	exit(0);
   }

   else
	printf("server acccept the client...\n");
	func(connfd);
	close(sockfd);
}
