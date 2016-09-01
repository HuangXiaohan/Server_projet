#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>  
      
#define PORT 8800 
#define MAXDATASIZE 100 

void process(FILE*fp, int sockfd);  
char *getMessage(char* sendline,int len, FILE* fp);  
      
int main(int argc,char *argv[]) {  
    int fd;  
    struct hostent  *he;  
    struct sockaddr_in  server;  
      
    if (argc !=2) {  
        printf("Usage:%s <IP Address>\n",argv[0]);  
        exit(1);  
    }  
      
    if((he=gethostbyname(argv[1]))==NULL){  
        printf("gethostbyname() error\n");  
        exit(1);  
    } 

    if((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
        printf("socket()error\n");  
        exit(1);  
    }  
      
    
    server.sin_family =AF_INET;  
    server.sin_port=htons(PORT);  
    server.sin_addr= *((struct in_addr *)he->h_addr);  
      
    if(connect(fd,(struct sockaddr *)&server,sizeof(server))==-1){  
        printf("connect() error\n");  
        exit(1);  
    }  

    printf("Connected to server. \n");  
    char sendline[MAXDATASIZE];
    while(1){
        if (fgets(sendline, MAXDATASIZE, stdin) != NULL) {  
            send(fd,sendline, strlen(sendline),0);  
        }   
    }
      
    close(fd);  
}  
      
void process(FILE *fp, int  sockfd)  {  
    char sendline[MAXDATASIZE],recvline[MAXDATASIZE]; 
    int num;

    if (fgets(sendline, MAXDATASIZE, fp) == NULL) {  
        printf("\nExit.\n");  
        return;  
    }  
    send(sockfd,sendline, strlen(sendline),0);  
    while(getMessage(sendline, MAXDATASIZE, fp) != NULL) {  
        send(sockfd,sendline, strlen(sendline),0);  
  
        if ((num =recv(sockfd, recvline, MAXDATASIZE,0)) == 0) {  
            printf("Server terminated.\n");  
            return;  
        }  
  
        recvline[num]='\0';  
        printf("%s\n",recvline);  
  
    }  
    printf("\nExit.\n");  
    
}  
      
char  *getMessage(char*  sendline,int len, FILE*  fp)  {  
    return(fgets(sendline,MAXDATASIZE, fp));  
}  