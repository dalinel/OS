#include <stdint.h>

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

typedef struct targa_header_ {
  uint8_t  idlength;
  uint8_t  colourmaptype;
  uint8_t  datatypecode;
  uint8_t useless[9];
  uint16_t width;
  uint16_t height;
  uint8_t useless2[2];
} targa_header;

int listeFichier(char * chemin);
int detecteTGA(char * name);
int readImage(fichierTGA * fc,targa_header * t, char * fName);
void affiche(fichierTGA * fc);
liste * ajoutFinDeListe(liste * l,char * fName);
liste * nouvelleListe(void);
fichierTGA * nouveauFichierTGA(void);

