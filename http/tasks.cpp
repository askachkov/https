
#include "tasks.h"
#include "utils.h"
#include <thread>

void http_Task()
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif//__WIN32__
     SOCKET sockfd, newsockfd;
     socklen_t clilen;

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
        if ( newsockfd != 0 ){
            printf("Socket %llu connected\n", newsockfd);
            std::thread (processClient,newsockfd).detach();
        }
     }
     close(sockfd);
#ifdef __WIN32__
     WSACleanup();
#endif//__WIN32__
}

void https_Task()
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif//__WIN32__
     SOCKET sockfd, newsockfd;
     socklen_t clilen;

     struct sockaddr_in serv_addr, cli_addr;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_SSL_NO);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while ( true ){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if ( newsockfd != 0 ){
            printf("Socket pre-ssl %llu connected\n", newsockfd);
            std::thread (processClientSSL,newsockfd).detach();
        }
     }
     close(sockfd);
#ifdef __WIN32__
     WSACleanup();
#endif//__WIN32__
}
