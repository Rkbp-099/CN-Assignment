#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>
#include <netdb.h>

#define SERVERPORT "3490"
#define BACKLOG 10

int main(){

	int i;
	char msg[100];
	socklen_t addr_size;

	int new_fd;
	
	fd_set writefds,readfds,writefdsm,readfdsm;
	
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

   

	strcpy(msg,"start");
	if((send(sockfd,msg,strlen(msg)+1,0))==-1){
		perror("send");
		return 0;
	}

	
//////////////////////////////////////////////////////////////////////////////

	
	FD_ZERO(&readfdsm);
	FD_SET(sockfd,&readfdsm);
	FD_SET(0,&readfdsm);

// //////////////////////////////////////////////////////////////////////////////

	printf("Chat started print \"bye\" (Case sensitive) to exit\n");

	while(1){
		
		readfds=readfdsm;

		if(select(sockfd+1,&readfds,NULL,NULL,NULL)==-1){
			perror("select");
			break;
		}

		for(i=0;i<=sockfd;++i){
			if(FD_ISSET(i,&readfds)){
				if(i==0){
					fgets(msg ,sizeof(msg),stdin);
					if((send(sockfd,msg,strlen(msg)+1,0))==-1){
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

		if(i<=sockfd)
			break;
	}

	close(sockfd);
	return(0);
}
