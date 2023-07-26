#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 9002 
#define MAX 1000
#define BACKLOG 5  
int main(){
    char serverMessage[MAX];
    char clientMessage[MAX];
    int choice,choice1,flag1;
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    char hostname[MAX], ipaddress[MAX];
    struct hostent *hostIP; 
    if(gethostname(hostname,sizeof(hostname))==0){
        hostIP = gethostbyname(hostname);//the netdb.h fucntion gethostbyname
    }
    else{
        printf("ERROR:FCC4539 IP Address Not ");
    }
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    connect(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    printf("\nLocalhost: %s\n", inet_ntoa(*(struct in_addr*)hostIP->h_addr));
    printf("Local Port: %d\n", PORT);
    printf("Remote Host: %s\n", inet_ntoa(serverAddress.sin_addr));
    flag1=1;
    while(flag1==1){
        printf("\n0.Stop\n1.Continue\nEnter your choice=");
        scanf("%d",&choice);
        if(choice==0){
            sprintf(serverMessage,"Result?");
            send(socketDescriptor, serverMessage, sizeof(serverMessage) , 0);
            recv(socketDescriptor, &clientMessage, sizeof(clientMessage), 0);
            flag1=0;
        }
        else{
              printf("1.Rounak\n2.Ayush\n3.Aman\nEnter your choice=");
              scanf("%d",&choice1);
              sprintf(serverMessage,"%d",choice1);
              send(socketDescriptor, serverMessage, sizeof(serverMessage) , 0);
              recv(socketDescriptor, &clientMessage, sizeof(clientMessage), 0) ;
        }
        puts(clientMessage); 
    }
    close(socketDescriptor);
    return 0;
}
