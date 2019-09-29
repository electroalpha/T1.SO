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

void obtenerNombre(int k, char* b){
    DIR *d;
    struct dirent *dir;
    d = opendir("Mazo");
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
