#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 200
#define PORT 1232
#define SA struct sockaddr

// Function for chat 
void chat(int connfd,int c)
{
    char buff[MAX],client_name[20];
    int n;

    if(c==0)
    {
        bzero(buff, MAX);
        printf("Enter the Username : ");

        // read the Username of the client
        read(connfd, buff, sizeof(buff));
        strncpy(client_name,buff,strlen(buff)-1);
        c++;
        bzero(buff, MAX);
        n = 0;
        
        // copy Server Username in the buffer
        while ((buff[n++] = getchar()) != '\n');
        
        // and send that Server Username to client
        write(connfd, buff, sizeof(buff));

        

    }
        // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // Reading the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        
        // print buffer which contains the client contents
        printf("%s : %s ",client_name, buff);
        bzero(buff, MAX);
        n = 0;
        
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        write(connfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit\n");
            break;
        }
    }
}

// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed\n");
        exit(0);
    }
     else    printf("Socket successfully created\n");
        
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed\n");
        exit(0);
    }
     else    printf("Socket binded\n");


    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Server listening failed\n");
        exit(0);
    }
     else printf("Server listening\n");

        
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Client failed to connnect\n");
        exit(0);
    }
     else printf("Client connected\n");

    
    
   int c=0;


    // Function for chatting 
    chat(connfd,c);

    // Closing the socket
    close(sockfd);
}
