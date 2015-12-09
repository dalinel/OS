/*
 * This program displays the names of all files in the current directory.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "main.h"
#include <stdlib.h>
#include <stddef.h>



int main(void)
{
    listeFichier(".");

    return 0;
}

/**
readImage(fichierTGA * fc,targa_header * t, char * fName)
Stocke dans la structure fichierTGA les champs nom, largeur et hauteur.
Ces données sont extraites à partir du header targa_header de l'image TGA désignée par fName.

Cette méthode retourne 0 si le fichier est introuvable et 1 si l'execution c'est déroulée normalement.
*/
int readImage(fichierTGA * fc,targa_header * t, char * fName){

    FILE * f=fopen(fName,"rb");
    if(f==NULL){
    printf("Oups pas de fichier\n");
    return 0;
    }
    else{

    fread(t, sizeof(targa_header), 1,f);

    fc->nom=fName;
    fc->largeur=t->width;
    fc->hauteur=t->height;
    fclose(f);
    return 1;
    }
}

/**
taille(fichierTGA* fc,char * name)
Stocke dans la structure fichierTGA le champs taille (en ko).
Ces données sont extraites grace à la méthode stat() appliquée à l'image TGA désignée par fName.

Cette méthode ne retourne rien.
*/
void taille(fichierTGA* fc,char * name){
    struct stat buff;
    stat(name, &buff);
    fc->tailleFichier=(buff.st_size)/1000;


}
/**
affiche(fichierTGA * fc)
Affiche les différents champs du fichierTGA fc

Cette méthode ne retourne rien.
*/
void affiche(fichierTGA * fc){
    printf("\nNom : %s\nTaille : %ldko.\nHauteur : %d pixels.\nLargeur : %d pixels.\n", fc->nom,fc->tailleFichier,fc->hauteur,fc->largeur);

}
/**
affiche(fichierTGA * fc)
Affiche les différents champs du fichierTGA fc

Cette méthode ne retourne rien.
*/
void afficheListe(liste * l){
   printf("Taille de la liste : %i\n",l->length);
   int i=0;
   fichierTGA * cour= nouveauFichierTGA();
   cour=l->head;
   for(i=0;i<(l->length);i++)
   {
        affiche(cour);
        cour=cour->next;

   }
}
/**
int detecteTGA(char * name)
Cette méthode détecte si name contient l'extension ".tga".

Si c'est le cas la méthode retourne 1 sinon elle retourne 0.
*/
int detecteTGA(char * name)
{
    char * i = strstr(name,".tga");
    if(i!=NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
/**
int listeFichier(char * chemin)
Cette méthode détecte les images tga contenu dans le répertoire chemin.

La méthode retourne 0 si l'éxecution s'est bien déroulée.
*/
int listeFichier(char * chemin){
    liste * l=nouvelleListe();


    DIR           *d;
    struct dirent *dir;
    d = opendir(chemin);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(detecteTGA(dir->d_name)==1)
            {

             l=ajoutFinDeListe(l,dir->d_name);


            }
        }

    afficheListe(l);
    free(l);
    closedir(d);
    }
    return(0);
}

/**
nouveauFichierTGA() instancie un objet fichierTGA
*/
fichierTGA * nouveauFichierTGA(void){

    fichierTGA * fc = malloc(sizeof * fc);
    if(fc!=NULL){
        fc->prev=NULL;
        fc->next=NULL;
        fc->hauteur=0;
        fc->largeur=0;
        fc->tailleFichier=0;
    }
    return fc;

}
/**
nouveauFichierTGA() instancie un objet liste
*/
liste * nouvelleListe(void)
{
    liste * l=malloc(sizeof * l);
    if(l!=NULL){
        l->length=0;
        l->head=NULL;
        l->tail=NULL;
    }
    return l;

}
/**
ajoutFinDeListe(liste * l,char * fName) rajoute à la fin de la liste l
un objet fichierTGA dont le contenu correspond à fName.
La liste étant doublement chainée la fonction instancie notamment les champs
prev et next de l'objetTGA.
*/
liste * ajoutFinDeListe(liste * l,char * fName)
{
    fichierTGA * fc = nouveauFichierTGA();
    targa_header * t = malloc(sizeof(targa_header));
    readImage(fc,t,fName);
    taille(fc,fName);

    if(fc != NULL)
    {
        l->length++;
        if(l->tail==NULL)
        {
            fc->next=NULL;
            fc->prev=NULL;
            l->head=fc;
            l->tail=fc;
            return l;
        }

        else
        {

            fc->next=NULL;
            fc->prev=l->tail;
            l->tail->next=fc;
            l->tail=fc;
            return l;

        }

    }
    return l;

}


