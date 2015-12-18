#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <strings.h> /* pour bcopy */
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>


typedef struct fichierTGA
{
    char * nom;
    long tailleFichier;
    int hauteur;
    int largeur;
    struct fichierTGA * next;
    struct fichierTGA * prev;
}fichierTGA ;

typedef struct liste
{
    int length;
    struct fichierTGA * head;
    struct fichierTGA * tail;

}liste;

/**Méthodes pour lister les images TGA*/
liste listeFichier(char * chemin);
liste * ajoutFinDeListe(liste * l,char * fName);
liste * nouvelleListe(void);
char * cherche(char * Buffer, liste l);

int vigenere(char * fName);
