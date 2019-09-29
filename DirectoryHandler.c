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
    d = opendir("/home/fabio/Escritorio/Universidad/SO/Tarea 1/Mazo");
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
