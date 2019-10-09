#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void){
    int client_socket;
    char client_message[256];
    struct sockaddr_in client_address;
    socklen_t client_len;
    int error_check;

    client_len = sizeof(client_address);

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1){
        printf("Error in socket.\n");
        exit(1);
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = INADDR_ANY;

    printf("Enter the message:-\n");
    fgets(client_message, sizeof(client_message), stdin);

    error_check = sendto(client_socket, client_message, sizeof(client_message), 0, (struct sockaddr *) &client_address, client_len);
    if (error_check == -1){
        printf("Error.\n");
        exit(1);
    }

    printf("message sent..\n");
    close(client_socket);
    return 0;
}