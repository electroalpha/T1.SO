#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


void CreateDirectoryIfNotExist(char s[]){
    mkdir(s, ACCESSPERMS);
}

void obtenerNombre(int k, char* b,char* dirname){
    DIR *d;
    struct dirent *dir;
    d = opendir(dirname);
    if (d){
        int i =0;
            while ((dir = readdir(d)) != NULL){
                if (i == k) {
                    strcpy(b,dir->d_name);
                }
                i++;
            }
            closedir(d);
        }
    }

void borrarAnt(){
    int b;
    for (b = 0; b < 4; b++) {
        char carpe[9] = "Jugador";
        char str[9];
        sprintf(str, "%d", b+1);
        strcat(carpe,str);
        DIR *d;
        struct dirent *dir;
        d = opendir(carpe);
        if (d){
            while ((dir = readdir(d)) != NULL){
                chdir(carpe);
                remove(dir->d_name);
                chdir("..");
                }
                closedir(d);
            }
    }
    DIR *d;
    struct dirent *dir;
    d = opendir("EnJuego");
    if (d){
        while ((dir = readdir(d)) != NULL){
            chdir("EnJuego");
            remove(dir->d_name);
            chdir("..");
            }
            closedir(d);
        }
}

int ChooseFile(char* dirname){
    DIR *d;
    struct dirent *dir;
    d = opendir(dirname);
    printf("-1: Sacar carta del mazo.\n");
    int i = 0;
    if (d){
        while((dir = readdir(d)) != NULL){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                printf("%d: ", i);
                printf("%s\n",dir->d_name);
                i++;
            }
        }

    }
    closedir(d);
    int eleccion;

    printf("Elige una carta.\n");
    int flag=0;
    while(flag==0){

        scanf("%d",&eleccion);
        if(eleccion < -1 || eleccion > i-1){
            printf("Elige una carta válida.\n");
        }
        else{
            flag = 1;
        }
    }
    return eleccion;
}

void MoveFile(char* dirOrg, char* dirDest, char* card){
    char temp[100];
    char temp2[100];
    strcpy(temp, dirOrg);
    strcpy(temp2,dirDest);

    strcat(temp,card);
    strcat(temp2,card);
    rename(temp,temp2);
}
