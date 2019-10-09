#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#define IP "10.42.0.203"

int main()
{
    int client_socket;
    int error_check;
    struct sockaddr_in client_address;
    socklen_t server_len;
    // char client_message[2];
    int dat[1];

    server_len = sizeof(client_address);

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket == -1)
    {
        printf("Error creating socket\n");
        exit(1);
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    // client_address.sin_addr.s_addr = INADDR_ANY;
    client_address.sin_addr.s_addr = inet_addr(IP);
    
    printf("Enter character to send\n");
    // fgets(dat, sizeof(dat[0]), stdin);
    scanf("%d",&dat[0]);
    // dat[1]  = 0;
    error_check = sendto(client_socket, dat, sizeof(dat),0, (struct sockaddr *) &client_address, server_len);
    if(error_check == -1)
    {
        printf("Error sending message\n");
        exit(1);
    }

    printf("message sent by client\n");

    close(client_socket);

    return 0;
}