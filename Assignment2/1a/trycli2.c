#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void){
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_len;
    char ping[10];
    char client_message[256];
    int error_check;
    client_len = sizeof(client_address);

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1){
        printf("error\n");
        exit(1);
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = INADDR_ANY;

    error_check = sendto(client_socket, ping, sizeof(ping), 0, (struct sockaddr *) &client_address, client_len);
    if (error_check == -1){
        printf("Error..\n");
        exit(1);
    }

    error_check = recvfrom(client_socket, client_message, sizeof(client_message), 0, (struct sockaddr *)&client_address, &client_len);
    if (error_check == -1){
        printf("Error.\n");
        exit(1);
    }

    printf("From server ==> %s", client_message);
    close(client_socket);
    return 0;
}