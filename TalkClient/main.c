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

int main(int argc, char *argv[])
{
int sock=0;
int i = 0;
char Buffer[1000]="rtyu";
struct sockaddr_in adr;


if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        i+=1;
        perror("Socket sock");
        exit(1);
    }

struct hostent * hote=gethostbyname(argv[1]);
    if (hote)
        puts(hote->h_name);
    else
        herror("gethostbyname");

adr.sin_family=AF_INET;
adr.sin_port=htons(6543);
bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);


if (connect(sock, (struct sockaddr *)&adr, sizeof(adr))==-1)
    {
        perror("connect");
        exit(1);
    }

ssize_t cb = send( sock, Buffer, cb, 0 );
if( cb == -1 )
    {
        perror( "send");
        exit(1);
    }
close(sock);
return 0;
}
