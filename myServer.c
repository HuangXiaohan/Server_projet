#include "myServer.h"

char *header = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n\r\n";

      
void process_cli(int connfd, struct sockaddr_in client)  {  
    char s1[10][80], s2[10][80], text[1024], line1[10][80];
    char *request, *path, *filename; 
    int len;
    request = malloc(sizeof(char *));


    //FILE *fp = fdopen(connfd,"r"); 
    //printf("======================\n");
    //while(fgets(requestline,1024,fp) != NULL) {
     //   printf("%s",requestline);
    //}
    //printf("======================\n");
    //printf("%s\n", request);


    recv(connfd,request,1028,0); //get the request of client
    printf("%s\n", request);

    len = split(s1,request,"\n");
    split(line1,s1[0]," ");

    setenv("REQUEST_METHOD",line1[0],1);  //set the request method in the environment
    //char *data = getenv("REQUEST_METHOD");
    //printf("%s\n", data);

    path = line1[1];
    printf("%s\n", path );

    if(strcmp(path,"/")==0||strcmp(path,"/index.html")==0){  //display the page of index
        FILE *file1 = fopen("index.html","r");
        send(connfd,header,strlen(header),0);
        while(fgets(text,1024,file1)!=NULL){
            //printf("%s\n",text);
            send(connfd,text,strlen(text),0);
        }
    }
    else if(strstr(path,"cgi-bin")!=NULL){    //ex: localhost:8800/cgi-bin/bonjour?nom=huang&prenom=xiaohan
        char *buffer1 = malloc(sizeof(char *));
        filename = malloc(sizeof(char*));
        char * method = getenv("REQUEST_METHOD");
        int i;

        if(strcmp(method,"GET")==0){
            split(s2, path,"?");
            path = s2[0];

            for(i = 0; i < strlen(path);i++){
                filename[i] = path[i+1];
            }
            filename[i+1] = '\0';
            printf("filename: %s\n", filename);

            setenv("QUERY_STRING",s2[1],1);
            //data = getenv("QUERY_STRING"); 
            //printf("%s\n",data );
            FILE *file2 = popen(filename,"r");
            send(connfd,header,strlen(header),0);  // send header
            while(fgets(buffer1,1024,file2) != NULL){
                //printf("%s",buffer1);
                send(connfd,buffer1,strlen(buffer1),0); 
            }
            pclose(file2);
        }
        else if(strcmp(method,"POST")==0){
            char *buffer2 = malloc(sizeof(char*));
            //printf("%s\n",s1[len-1] );
            int j;
            for(j = 0; j < strlen(path);j++){
                filename[j] = line1[1][j+1];
            }
            filename[j+1] = '\0';
            printf("filename: %s\n",filename);
            setenv("QUERY_STRING",s1[len-1],1);
            FILE *file3 = popen(filename,"r");
            send(connfd,header,strlen(header),0);
            while(fgets(buffer2,1024,file3) != NULL){
                send(connfd,buffer2,strlen(buffer2),0); 
            }
            pclose(file3);
        }
        
    }

    close(connfd);  

} 

int split(char dst[][80], char* str, const char* spl)
{
    int n = 0;
    char *result = NULL;
    result = strtok(str, spl);
    while( result != NULL )
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }
    return n;
}







