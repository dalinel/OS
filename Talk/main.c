#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <strings.h> /* pour bcopy */
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

int main(){

struct sockaddr_in addr;
int socket_RV,socket_service;
int i=0;
char nom[30];
nom[29]='\0';
char Buffer[1000];


if((socket_RV=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        i+=1;
        perror("Socket rendez vous");
        exit(1);
     }

if(gethostname(nom,30)==1)
    {
    i+=1;
    perror("Qui suis je ?");
    exit(1);
    }
printf("Machine %s\n",nom);

addr.sin_family=AF_INET;
addr.sin_port=htons(6543);
addr.sin_addr.s_addr=htons(INADDR_ANY);
if (bind(socket_RV,(struct sockaddr *)&addr,sizeof(addr))==-1)
    {
        i+=1;
        perror("Bind");
        exit(1);
    }
if (listen(socket_RV,1)==-1)
    {
        i+=1;
        perror("Listen");
        exit(1);
    }

if(i==0)
    {
        socklen_t * size=malloc(sizeof(socklen_t));
        socket_service=accept(socket_RV,(struct sockaddr *) &addr, size);

        ssize_t cb =recv(socket_service,Buffer,sizeof(Buffer),0);
        if(cb <= 0)
        {
            perror("receive");
            exit(1);
        }
        else
        {
            printf("%s\n",Buffer);
        }
    }
close(socket_RV);
return 0;
}

