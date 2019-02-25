/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "utils.h"
#include <thread>

int main(int argc, char *argv[])
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif//__WIN32__
     SOCKET sockfd, newsockfd;
     int clilen;

     struct sockaddr_in serv_addr, cli_addr;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_NO);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while ( true ){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if ( newsockfd != INVALID_SOCKET ){
            printf("Socket %llu connected\n", newsockfd);
            std::thread (processClient,newsockfd).detach();
        }
     }
     closesocket(sockfd);
#ifdef __WIN32__
     WSACleanup();
#endif//__WIN32__
     return 0;
}
