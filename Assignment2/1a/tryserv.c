#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void){
    int server_socket;
    struct sockaddr_in client_address;
    socklen_t client_len;
    char server_message[256];
    char ping[2];
    int error_check;

    client_len = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0); 
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    error_check = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (error_check == -1){
        printf("Error occurred in binding.\n");
        exit(1);
    }

    error_check = recvfrom(server_socket, server_message, sizeof(server_message), 0, (struct sockaddr *) &client_address, &client_len);
    if (error_check == -1){
        printf("Error occurred in receiving 1\n");
        exit(1);
    }

    printf("From client1 ==> %s", server_message);


    error_check = recvfrom(server_socket, ping, sizeof(ping), 0, (struct sockaddr *) &client_address, &client_len);
    if (error_check == -1){
        printf("Error in ping.\n");
        exit(1);
    }

    error_check = sendto(server_socket, server_message, sizeof(server_message), 0, (struct sockaddr *) &client_address, client_len);
    if (error_check == -1){
        printf("Error in sending to client2.\n");
        exit(1);
    }   

    printf("Server is done..\n");
    close(server_socket);
    return 0;
}