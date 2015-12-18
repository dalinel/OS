#include "EncrypterDecrypter.h"

/**
int main()
{
    vigenere("bob.tga");
    return 0;
}
*/

int vigenere(char * fName){

    //char * key ="I count six shot nigga' ! I count two guns nigga'!";
    char * key ="Praise the lord!";

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
