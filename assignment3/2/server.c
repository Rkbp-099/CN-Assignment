#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>


int main(){

	int i;
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

   int new_fd = accept(sockfd,NULL,NULL);

   if(new_fd==-1)
   {
      printf("error in picking up the call \n");
      return 0;
   }
   // char msg[256];
	char msg2[100];
	recv(new_fd,msg2,sizeof(msg2),0);
	printf("accepted new:%d -- %s \n",new_fd,msg2);

	
//////////////////////////////////////////////////////////////////////////////

	fd_set writefds,readfds,writefdsm,readfdsm;
	
	FD_ZERO(&readfdsm);
	FD_SET(new_fd,&readfdsm);
	FD_SET(0,&readfdsm);//fd  for stdin

// //////////////////////////////////////////////////////////////////////////////


	char msg[100];
	printf("Chat started print \"bye\" (Case sensitive) to exit\n");

	while(1){
		

		readfds=readfdsm;


		if(select(new_fd+1,&readfds,NULL,NULL,NULL)==-1){
			perror("select");
			break;
		}


		for(i=0;i<=new_fd;++i){
			if(FD_ISSET(i,&readfds)){
				if(i==0){

					fgets(msg ,sizeof(msg),stdin);
					if((send(new_fd,msg,strlen(msg)+1,0))==-1){
							perror("send");
							break;
					}
					if(strncmp("bye",msg,3)==0)
						break;
				}
				else {
					int temp=(recv(i,msg,sizeof(msg),0));
					if(temp==-1){
						perror("recv");
						break;
					}
					if(temp==0){
						printf("They exited");
						break;
					}
					printf("\n==msg==\n");
					printf("%s\n", msg);
					fflush(stdout);

					if(strncmp("bye",msg,3)==0)
						break;
				}
			}
		}

		if(i<=new_fd)
			break;
	}

	close(new_fd);
	close(sockfd);
	return(0);
}
