#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main()
{
    vigenere("bob.tga");
    return 0;
}

int vigenere(char * fName){

    char * key ="I count six shot nigga' ! I count two guns nigga'!";


    int int_key=0;


    clone(fName,"vigenere.tga");

    image_desc * pDesc = malloc(sizeof(image_desc));
    targa_header * t = malloc(sizeof(targa_header));
    if(readImage(pDesc,t,"vigenere.tga")==0){
        int i=0;
        int j=0;
        int size=pDesc->width*pDesc->height;

            for(i=0;i<size;i++){

                int_key = (int)key[j%strlen(key)];
                pDesc->pRed[i]=(pDesc->pRed[i]+int_key)%256;
                j++;
                int_key = (int)key[j%strlen(key)];
                pDesc->pGreen[i]=(pDesc->pGreen[i]+int_key)%256;
                j++;
                int_key = (int)key[j%strlen(key)];
                pDesc->pBlue[i]=(pDesc->pBlue[i]+int_key)%256;
                j++;
                int_key = (int)key[j%strlen(key)];

            }
            j=0;
            for(i=0;i<size;i++){

                int_key = ((int)key[j%strlen(key)])*size/255;
                pDesc->pRed[i]=pDesc->pRed[(i+int_key)%size];
                j++;
                int_key = (int)key[j%strlen(key)];
                pDesc->pGreen[i]=pDesc->pGreen[(i+int_key)%size];
                j++;
                int_key = (int)key[j%strlen(key)];
                pDesc->pBlue[i]=pDesc->pBlue[(i+int_key)%size];

            }
            writeImage(*pDesc,*t,"vigenere.tga");

    }
    return 0;

}
int readImage(image_desc *pDesc,targa_header * t, char * fName){

    FILE * f=fopen(fName,"rb");
    if(f==NULL){
    printf("oups pas de fichier");
    return 1;
    }
    else{

    fread(t, sizeof(targa_header), 1,f);
    pDesc->fname=fName;
    pDesc->width=t->width;
    pDesc->height=t->height;
    pDesc->pRed = malloc(t->width*t->height);
    pDesc->pGreen = malloc(t->width*t->height);
    pDesc->pBlue = malloc(t->width*t->height);

    int i;
    for(i=0;i<(t->width*t->height);i++){

        fread(pDesc->pRed+i,sizeof(uint8_t),1,f);
        fread(pDesc->pGreen+i,sizeof(uint8_t),1,f);
        fread(pDesc->pBlue+i,sizeof(uint8_t),1,f);

    }

    fclose(f);
    return 0;
    }
}

int writeImage(image_desc pDesc,targa_header t, char* fName){

FILE * f=fopen(fName,"wb");

 if(f==NULL){
    printf("oups pas de fichier");
    return 1;
    }
else{

    fwrite(&t,sizeof(targa_header),1,f);


        int i;
        for(i=0;i<pDesc.width*pDesc.height;i++){

           fwrite(pDesc.pRed+i,sizeof(uint8_t),1,f);
           fwrite(pDesc.pGreen+i,sizeof(uint8_t),1,f);
           fwrite(pDesc.pBlue+i,sizeof(uint8_t),1,f);
    }
}

fclose(f);
return 0;

}
int clone(char fName[],char fName1[]){

image_desc *pDesc = malloc(sizeof(image_desc));
targa_header * t = malloc(sizeof(targa_header));
int f = readImage(pDesc,t,fName );
int f1 = writeImage(*pDesc,*t,fName1);
printf("lecture %d",f);
printf("ecriture %d",f1);
return 0;

}
