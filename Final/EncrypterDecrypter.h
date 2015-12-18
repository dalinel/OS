#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


/* Une structure pour decrire les elements d'image utiles au traitement */
typedef struct image_desc_
{
  char *fname;               /* Libellé du fichier image (path)                 */
  uint16_t width;
  uint16_t height;
  uint8_t *pRed;               /* Référence sur le plan mémoire de couleur rouge  */
  uint8_t *pBlue;              /* Référence sur le plan mémoire de couleur bleue  */
  uint8_t *pGreen;             /* Référence sur le plan mémoire de couleur verte  */
} image_desc ;

int vigenere(char * fName);
int readImage(image_desc *pDesc,targa_header * t, char * fName);
int writeImage(image_desc pDesc,targa_header t, char* fName);
int clone(char fName[],char fName1[]);
