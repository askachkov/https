
#include "tasks.h"
#include <thread>

void default_Task(F fnc, uint16_t port)
{
     SOCKET sockfd, newsockfd;
     socklen_t clilen;

     struct sockaddr_in serv_addr, cli_addr;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while ( true ){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if ( newsockfd != 0 ){
            printf("Socket %llu connected\n", newsockfd);
            std::thread (fnc,newsockfd).detach();
        }
     }
     close(sockfd);
}
