#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 200
#define PORT 1232
#define SA struct sockaddr
void chat(int sockfd,int c)
{
    char buff[MAX],server_name[20];
    int n;
    
    if(c==0)
    {
        bzero(buff, sizeof(buff));
        printf("Enter the Username : ");
        n = 0;
        
        //copy Client Userneme in the buffer
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        strncpy(server_name,buff,strlen(buff)-1);
        c++;

    }
    for (;;) {
        bzero(buff, sizeof(buff));

        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("%s: %s", server_name, buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket could not be created\n");
        exit(0);
    }
     else printf("Socket successfully created\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Failed to connect to the server\n");
        exit(0);
    }
     else printf("connected to the server\n");


    
    int c=0;
    

    // function for chat
    chat(sockfd, c);

    // close the socket
    close(sockfd);
}
