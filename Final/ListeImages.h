#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stddef.h>

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

/* Un header targa basique. */
typedef struct targa_header_ {
  uint8_t  idlength;
  uint8_t  colourmaptype;
  uint8_t  datatypecode;
  uint8_t useless[9];
  uint16_t width;
  uint16_t height;
  uint8_t useless2[2];
} targa_header;


/**Méthodes pour lister les images TGA*/
liste listeFichier(char * chemin);
int detecteTGA(char * name);
int litImage(fichierTGA * fc,targa_header * t, char * fName);
void affiche(fichierTGA * fc);
liste * ajoutFinDeListe(liste * l,char * fName);
liste * nouvelleListe(void);
fichierTGA * nouveauFichierTGA(void);
char * cherche(char * Buffer, liste l);


