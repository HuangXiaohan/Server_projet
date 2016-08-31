#ifndef __MY_SERVER_H__
#define __MY_SERVER_H__
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <sys/epoll.h>
#include <fcntl.h>
#include <assert.h>


void process_cli(int  connfd, struct sockaddr_in client);  
int split(char dst[][80], char* str, const char* spl);

#endif  