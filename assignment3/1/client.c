#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

int main()
{
   
   int sockfd=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in server_address;
   server_address.sin_family=AF_INET;
   server_address.sin_port=htons(9002);
   server_address.sin_addr.s_addr=INADDR_ANY;

   int connection_status = connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));

   if(connection_status==-1)
   {
      printf("error in connecting to server \n");
      return 0;
   }

   char msg[256];

   while(1)
   {
      //recieve message from server in the array
      recv(sockfd,&msg,sizeof(msg),0);
      printf("Server : %s",msg);
      
      //if input from server is bye exit
      if(strncmp(msg,"bye",3)==0)
         break;
      
      //client will send message 
      printf("Client : ");
      fgets(msg,sizeof(msg),stdin);
         
      //if input from stdin is bye send message to server and exit
      //use strlen in send but size is recv 
      send(sockfd,msg,strlen(msg)+1,0);

      if(strncmp(msg,"bye",3)==0)
         break;
      
   }

   close(sockfd);
   return 0;
}