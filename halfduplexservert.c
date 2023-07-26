#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define h_addr h_addr_list[0]
#define PORT 9002 
#define MAX 1000 
#define BACKLOG 5 
int main()
{
    char serverResponse[MAX];
    char clientResponse[MAX];
    int i=0;
    int j=0;
    int k=0;
    char ch;
    int max;
    int flag=1;
    int  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));    
    listen(socketDescriptor, BACKLOG);
    int clientSocketDescriptor = accept(socketDescriptor, NULL, NULL);
    while (flag==1){
        recv(clientSocketDescriptor, serverResponse, sizeof(serverResponse), 0);
        printf("\nSERVER: %s", serverResponse);
        printf("\n");
        if(strcmp(serverResponse,"Result?")==0){
            if(i>j){
                if(i>k)
                    max=i;
                else
                    max=k;
            }
            else{
                if(j>k)
                    max=j;
                else
                    max=k;
            }
            printf("Rounak=%d\nAyush=%d\nAman=%d",i,j,k);
            if((i==j)&&(j==k))
                sprintf(clientResponse,"Rounak,ayush  and aman all 3 are winners");
            else if((max==i)&&(i==j))
                sprintf(clientResponse,"Rounak and ayush both winner");
            else if((max==i)&&(i==k))
                sprintf(clientResponse,"Rounak and aman both winner");
            else if((max==j)&&(j==k))
                sprintf(clientResponse,"Aman and ayush both winner");
            else if(max==i)
                sprintf(clientResponse,"Rounak is Winner");
            else if(max==j)
                sprintf(clientResponse,"Ayush is Winner");
            else if(max==k)
                sprintf(clientResponse,"Aman is Winner");
            send(clientSocketDescriptor, clientResponse, sizeof(clientResponse), 0);
            flag=0;
        }
        else{
            if(strcmp(serverResponse,"1")==0){
                i++;
                sprintf(clientResponse,"Rounak");
                printf("%s",clientResponse);
            }
            if(strcmp(serverResponse,"2")==0){
                j++;
                sprintf(clientResponse,"Ayush");
                printf("%s",clientResponse);
            }
            if(strcmp(serverResponse,"3")==0){
                k++;
                sprintf(clientResponse,"Aman");
                printf("%s",clientResponse);
            }
            send(clientSocketDescriptor, clientResponse, sizeof(clientResponse), 0);
        }
    }
    close(socketDescriptor);
    return 0;
}
