#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DirectoryHandler.h"
#include <dirent.h>
#include <fcntl.h>


int MenuPrincipal(){
  int option;
  printf("¡Bienvenido a UNO!\n");
  printf("Elija la opcion a ejecutar\n");
  printf("1: Iniciar Juego\n");
  printf("0: Salir\n");
  scanf("%d", &option);
  printf("----------------------\n");
  return option;
}

int main(){

  // Se crea la carpeta Mazo

  char carp[5] = "Mazo";
  CreateDirectoryIfNotExist(carp);

  // Comienza el proceso de creacion de las cartas de colores

  // Cada for crea todos los tipos de cartas de un color

  int i;
  for (i = 0; i < 4; i ++){
    char color[10];
    switch(i){
        case 0:
            strcpy(color, "verde");
            break;
        case 1:
            strcpy(color, "rojo");
            break;
        case 2:
            strcpy(color, "azul");
            break;
        case 3:
            strcpy(color, "amarillo");
            break;
    }
    int j;
    for (j = 0; j <= 12; j++){
      char buffer[260];
      char fileName[100];

      // Ya que solo existe un 0 por color, se crean estos primero

      if (j == 0){
        sprintf(fileName, "%d ", j);
        strcat(fileName, color);
        snprintf(buffer, sizeof(buffer), "Mazo/%s.txt", fileName);
        int file = open(buffer, O_CREAT,S_IRUSR | S_IROTH|S_IXUSR|S_IXOTH);
        close(file);
      }

      // Luego se crea el resto de cartas, 2 de cada tipo

      else{
        int k;
        for (k = 1; k < 3; k++){
          if (j == 10){
            char rev[10] = "salto ";
            sprintf(fileName, "%s",rev);
            strcat(fileName, color);
          }
          else if (j == 11){
            char rev[10] = "reversa ";
            sprintf(fileName, "%s",rev);
            strcat(fileName, color);
          }
          else if (j == 12){
            char rev[5] = "+2 ";
            sprintf(fileName, "%s",rev);
            strcat(fileName, color);
          }
          else{
            sprintf(fileName, "%d ", j);
            strcat(fileName, color);
          }
          char temp[5];
          sprintf(temp, " (%d)", k);
          strcat(fileName, temp);

          snprintf(buffer, sizeof(buffer), "Mazo/%s.txt", fileName);
          int file = open(buffer, O_CREAT,S_IRUSR | S_IROTH|S_IXUSR|S_IXOTH);
          close(file);
          }
        }
    }
  }

  // Se crean las cartas negras, 4 de cada tipo

  int l;
  for (l = 0 ; l < 2 ; l++){
    char buffer[260];
    int i;
    for (i = 1; i < 5; i++ ){
      if(l == 0){
        snprintf(buffer, sizeof(buffer), "Mazo/cambio de color (%d).txt", i);
        int file = open(buffer, O_CREAT,S_IRUSR | S_IROTH|S_IXUSR|S_IXOTH);
        close(file);
      }
      else{
        snprintf(buffer, sizeof(buffer), "Mazo/+4 (%d).txt", i);
        int file = open(buffer, O_CREAT,S_IRUSR | S_IROTH|S_IXUSR|S_IXOTH);
        close(file);
      }
    }
  }

  // Menu principal del juego

  int opcion = MenuPrincipal();
  if (opcion == 0){
    printf("Has salido del juego.\n");
    printf("----------------------\n");
    return 0;
  }
  // Se comienza el proceso para crear jugadores

  // Se crea una carpeta para cada jugador

  int b;

  for (b = 0; b < 4; b++) {
      char carpe[9] = "Jugador";
      char str[9];
      sprintf(str, "%d", b+1);
      strcat(carpe,str);
      CreateDirectoryIfNotExist(carpe);
  }

  // Se crea la carpeta que contendra las cartas ya jugadas

  char str[8]= "EnJuego";
  CreateDirectoryIfNotExist(str);

  // Se reparten lan cartas aleatoriamente en cada carpeta de Jugador, siendo 7 para cada uno

  int k =108;
  int g = 0;
  char card[15];

  while (g<29) {
      int temp = rand()%(k+1);
      char b[15];
      obtenerNombre(temp,b);
      strcpy(card,b);
      if (!((strcmp(card,".")== 0) || (strcmp(card,"..") ==0))){
          if (g<7) {
              char* source = malloc(sizeof(char)*255);
              strcpy(source, "Mazo/");

              char* dest = malloc(sizeof(char)*500);
              strcpy(dest, "Jugador1/");

              strcat(source,card);
              strcat(dest,card);
              rename(source,dest);
              free((void*)dest);
              free((void*)source);
          }
          else if (g >= 7 && g <14) {
              char* source = malloc(sizeof(char)*255);
              strcpy(source, "Mazo/");

              char* dest = malloc(sizeof(char)*500);
              strcpy(dest, "Jugador2/");

              strcat(source,card);
              strcat(dest,card);
              rename(source,dest);
              free((void*)dest);
              free((void*)source);
          }
          else if (g >= 14 && g <21) {
              char* source = malloc(sizeof(char)*255);
              strcpy(source, "Mazo/");

              char* dest = malloc(sizeof(char)*500);
              strcpy(dest, "Jugador3/");

              strcat(source,card);
              strcat(dest,card);
              rename(source,dest);
              free((void*)dest);
              free((void*)source);
          }
          else if (g >= 21 && g <28) {
              char* source = malloc(sizeof(char)*255);
              strcpy(source, "Mazo/");

              char* dest = malloc(sizeof(char)*500);
              strcpy(dest, "Jugador4/");

              strcat(source,card);
              strcat(dest,card);
              rename(source,dest);
              free((void*)dest);
              free((void*)source);
          }
          else{
              char* source = malloc(sizeof(char)*255);
              strcpy(source, "Mazo/");

              char* dest = malloc(sizeof(char)*500);
              strcpy(dest, "EnJuego/");

              strcat(source,card);
              strcat(dest,card);
              rename(source,dest);
              free((void*)dest);
              free((void*)source);
          }
          strcpy(b,"");
          g++;
          k--;
      }

  }


  // En construccion...

  printf("perdiste F\n");
  printf("----------------------\n");
  return 0;
}
