#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "DirectoryHandler.h"
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>


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

  //Se borran cartas si es que quedaron de juegos anteriores en sus carpetas correspondientes
  borrarAnt();

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
      srand(time(NULL));
      int temp = rand()%(k+1);
      char b[15];
      obtenerNombre(temp,b,"Mazo");
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

  int y;
  int player =1;
  int bucle =1;
  int nbytes=0; //cuantos bytes se han escrito o leido del pipe
  char strGrande[256];
  int priJu = 0;
  int pipePH[6];
  int pipeHP[6];
  int f;
  int h;
  // crear hijos y pipes
  for (f = 0; f < 3; f++) {
    pipe(&pipePH[2*f]);
  }
  for (h = 0;h< 3; h++) {
    pipe(&pipeHP[2*h]);
  }
  for ( y = 1; y < 4; y++) {
    int pid;
    pid = fork();
    if (pid == 0){
      player+=y;// indica que jugador es cada uno
      break;
    }
  }

  switch (player) {//ordenados por jugadores
    case 1:// Padre
      close(pipeHP[1]);// cierro escritura HP
      close(pipeHP[3]);
      close(pipeHP[5]);
      close(pipePH[0]);// cierro lectura padre al hijo
      close(pipePH[2]);
      close(pipePH[4]);

      while (bucle==1){
        bzero(strGrande,256);
        char jugada[60];
        if (priJu==0){
          printf("Empieza el player 1\nQue desea hacer P1[jugar/fin]: ");
          bzero(strGrande,256);
          scanf("%s",strGrande);
          if (strcmp(strGrande,"jugar")==0){
            printf("Player 1 jugó por primera vez\nSe le comunica al jugador 2 su turno\n");
            write(pipePH[1],strGrande,strlen(strGrande));
          }
          else{
            printf("Se acabo el juego\n");
            strcpy(jugada,"fin");
            write(pipePH[1],jugada,strlen(jugada));
            write(pipePH[3],jugada,strlen(jugada));
            write(pipePH[5],jugada,strlen(jugada));
            wait(NULL);
            break;
          }
        }
        priJu =1;
        bzero(strGrande,256);
        nbytes = read(pipeHP[0],strGrande,256);
        if (strcmp(strGrande,"jugar")==0){
          printf("Jugador 2 jugo.\nSe le comunica al jugador 3 su turno\n");
          write(pipePH[3],strGrande,strlen(strGrande));
        }
        else{
          printf("Jugador 2 finalizo el juego.\nSe acabo el juego\n");
          strcpy(jugada,"fin");
          write(pipePH[1],jugada,strlen(jugada));
          write(pipePH[3],jugada,strlen(jugada));
          write(pipePH[5],jugada,strlen(jugada));
          wait(NULL);
          bucle = 0;
          break;
        }
        bzero(strGrande,256);
        nbytes = read(pipeHP[2],strGrande,256);
        if (strcmp(strGrande,"jugar")==0){
          printf("Jugador 3 jugo.\nSe le comunica al jugador 4 su turno\n");
          write(pipePH[5],strGrande,strlen(strGrande));
        }
        else{
          printf("Jugador 3 finalizo el juego.\nSe acabo el juego\n");
          strcpy(jugada,"fin");
          write(pipePH[1],jugada,strlen(jugada));
          write(pipePH[3],jugada,strlen(jugada));
          write(pipePH[5],jugada,strlen(jugada));
          wait(NULL);
          bucle = 0;
          break;
        }
        bzero(strGrande,256);
        nbytes = read(pipeHP[4],strGrande,256);
        if (strcmp(strGrande,"jugar")==0){
          printf("Jugador 4 jugo.\nSe le comunica al jugador 1 su turno\n");
          printf("Que desea hacer P1[jugar/fin]: ");
          bzero(strGrande,256);
          scanf("%s",strGrande);
          if (strcmp(strGrande,"jugar")==0){
            printf("Player 1 jugó.\n Se le comunica al jugador 2 su turno\n");
            write(pipePH[1],strGrande,strlen(strGrande));
          }
          else{
            printf("Se acabo el juego\n");
            strcpy(jugada,"fin");
            write(pipePH[1],jugada,strlen(jugada));
            write(pipePH[3],jugada,strlen(jugada));
            write(pipePH[5],jugada,strlen(jugada));
            wait(NULL);
            break;
          }
        }
        else{
          printf("Se acabo el juego\n");
          strcpy(jugada,"fin");
          write(pipePH[1],jugada,strlen(jugada));
          write(pipePH[3],jugada,strlen(jugada));
          write(pipePH[5],jugada,strlen(jugada));
          wait(NULL);
          bucle = 0;
          break;
        }
      }
    break;
    case 2: //HIJOS
      close(pipeHP[0]);
      close(pipePH[1]);
      while(bucle==1){
        bzero(strGrande,256);
        nbytes = read(pipePH[0],strGrande,256);
        if ( strcmp("jugar", strGrande) == 0) {
          printf("Voy a jugar, soy el 2\nQue desea hacer P2[jugar/fin]: ");
          bzero(strGrande,256);
          scanf("%s",strGrande);
          write(pipeHP[1],strGrande,strlen(strGrande));
        }
        else{
          bucle = 0;
          break;
        }
      }
     break;
     case 3: //HIJOS
       close(pipeHP[2]);
       close(pipePH[3]);
       while(bucle==1){
          bzero(strGrande,256);
          nbytes = read(pipePH[2],strGrande,256);
          if ( strcmp("jugar", strGrande) == 0) {
            printf("Voy a jugar, soy el 3\nQue desea hacer P3[jugar/fin]: ");
            bzero(strGrande,256);
            scanf("%s",strGrande);
            write(pipeHP[3],strGrande,strlen(strGrande));
          }
          else{
            bucle =0;
            break;
          }
        }
      break;
      case 4://HIJOS
        close(pipeHP[4]);
        close(pipePH[5]);
        while(bucle==1){
           bzero(strGrande,256);
           nbytes = read(pipePH[4],strGrande,256);
           if ( strcmp("jugar", strGrande) == 0) {
             printf("Voy a jugar, soy el 4\nQue desea hacer P4[jugar/fin]: ");
             bzero(strGrande,256);
             scanf("%s",strGrande);
             write(pipeHP[5],strGrande,strlen(strGrande));
           }
           else{
             bucle =0;
             break;
           }
         }
       break;
    }
  // En construccion...
  printf("----------------------\n");
  return 0;
}
