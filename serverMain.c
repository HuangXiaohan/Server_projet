#include "myServer.h"

extern char **environ; 
      
#define PORT 8800 
#define BACKLOG 5 
//#define MAXDATASIZE 1000

//void process_cli(int  connfd, struct sockaddr_in client); 
  
int main(int argc,char *argv[]) {  
    int  listenfd, connfd;  
    pid_t  pid;  
    struct  sockaddr_in  server;  
    struct sockaddr_in  client;  
    int  len;  
      
    if ((listenfd =socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("Creatingsocket failed.");  
        exit(1);  
    }  
      
    int opt =SO_REUSEADDR;  
    setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));    
    bzero(&server, sizeof(server));

    server.sin_family=AF_INET;  
    server.sin_port=htons(PORT);  
    server.sin_addr.s_addr= htonl (INADDR_ANY);  

    if (bind(listenfd,(struct sockaddr *)&server, sizeof(server)) == -1) {  
        perror("Bind()error.");  
        exit(1);  
    }  
      
    if(listen(listenfd,BACKLOG)== -1){  
        perror("listen() error\n");  
        exit(1);  
    } 

    printf("Serving on port %d ...\n", PORT);

    len=sizeof(client);  

    while(1) { 

        if ((connfd =accept(listenfd,(struct sockaddr *)&client, &len))==-1) {  
            perror("accept() error\n");  
            exit(1);  
        }  

        if ((pid=fork())>0){  
            close(connfd);  
            continue;  
        } 

        else if (pid==0) { 
            close(listenfd);  
            process_cli(connfd, client); 
            exit(0);  
        }  
        else {  
            printf("fork() error\n");  
            exit(0);  
        } 

    }

    close(listenfd);  

    return 0;
} 
