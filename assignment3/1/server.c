#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

int main()
{

   int sockfd=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in server_address;
   server_address.sin_family=AF_INET;
   server_address.sin_port=htons(9002);
   server_address.sin_addr.s_addr=INADDR_ANY;

   int status;
   status=bind(sockfd,(struct sockaddr*)&server_address,sizeof(server_address));
   
   if(status==-1)
   {
      printf("error in bind \n");
      return 0;
   }
   
   status=listen(sockfd,5);
   if(status==-1)
   {
      printf("error in listening \n");
      return 0;
   }

   int clientfd = accept(sockfd,NULL,NULL);

   if(clientfd==-1)
   {
      printf("error in picking up the call \n");
      return 0;
   }
   char msg[256];
   

   while(1)
   {
      printf("Server : ");
      fgets(msg,sizeof(msg),stdin);
      send(clientfd,msg,strlen(msg)+1,0);
      
      //if the message send by server to client is bye then exit
      if(strncmp(msg,"bye",3)==0)
         break;

      recv(clientfd,msg,sizeof(msg),0);
      printf("Client : %s",msg);

      //if input from use is bye exit
      if(strncmp(msg,"bye",3)==0)
         break;
   }
   close(sockfd);
   return 0;
}