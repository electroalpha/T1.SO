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

  int y;
  int player =1;
  int bucle =1;
  int nbytes=0; //cuantos bytes se han escrito o leido del pipe
  char strGrande[256];
  int priJu = 0;
  int pipePH[6];
  int pipeHP[6];
  int f;
  // crear hijos y pipes
  for (f = 0; f < 3; f++) {
    pipe(&pipePH[2*f]);
}
  int h;
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
      while(bucle){
          bzero(strGrande,256);
          char jugada[60];
          if (priJu==0){
            printf("Player 1 jugó por primera vez \n");
            strcpy(jugada,"jugar");
            write(pipePH[1],jugada,strlen(jugada));
          }
          else {
            bzero(strGrande,256);
            if ((nbytes = read(pipeHP[0],strGrande,256))!=0){//Corroboran si la llamada viene de otro jugador pero no le corresponde jugar al 1
              if ((strstr(strGrande, "jugar"))!=NULL){
                write(pipePH[3],strGrande,strlen(strGrande));// le mando la señan al jugador 3 que tiene que jugar
                printf("Juega el jugador 2, Se le avisa al jugador 3 que juegue\n");
              }
              else if ((strstr(strGrande, "saltar"))!=NULL){
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que jugar
                printf("Juega el jugador 2,Se le avisa al jugador 4 que juegue,porque el 3 fue saltado\n");
              }
              else if ((strstr(strGrande, "+2+4"))!=NULL){
                write(pipePH[3],strGrande,strlen(strGrande));// le mando la señan al jugador 3 que tiene que robar
                printf("Juega el jugador 2,Se le avisa al jugador 3 que robe\n");
              }
              else if((strstr(strGrande, "reversa"))!=NULL){
                printf("Juega el jugador 2, luego Jugador 1 juega carta por el reversa del Jugador 2\n");
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que jugar
                printf("Se le avisa al jugador 4 que juege\n");
              }
              else if ((strstr(strGrande, "jugarR"))!=NULL){
                // le mando la señan al jugador 1 que tiene que jugar
                printf("Juega el jugador 2, Se le avisa al jugador 1 que juegue, El jugador 1 juega \n");
              }
              else if ((strstr(strGrande, "saltarR"))!=NULL){
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que jugar
                printf("Juega el jugador 2,Se le avisa al jugador 4 que juegue,porque el 1 fue saltado\n");
              }
              else if ((strstr(strGrande, "+2+4R"))!=NULL){
                // le mando la señan al jugador 1 que tiene que robar
                printf("Juega el jugador 2,Se le avisa al jugador 1 que robe,El jugador 1 roba.\n");
                strcpy(strGrande,"juegaR");
                write(pipePH[5],strGrande,strlen(strGrande));// se le dice al 4 que juegue porque ya roobo
                printf("Se le dice al jugador 4 que juegue, porque el jugador 1 ya robo\n");

              }
              else if((strstr(strGrande, "reversaR"))!=NULL){
                printf("Juega el jugador 2, luego Jugador 3 juega carta por el reversa del Jugador 2\n");
                write(pipePH[3],strGrande,strlen(strGrande));// le mando la señan al jugador 3 que tiene que jugar
                printf("Se le avisa al jugador 3 que juege\n");
              }
              else if((strstr(strGrande, "fin"))!=NULL){
                write(pipePH[3],strGrande,strlen(strGrande));//fin
                write(pipePH[5],strGrande,strlen(strGrande));
                wait(NULL);
                printf("Se Acabo el juego\n");
                bucle = 0;
              }
            }
            else if((nbytes = read(pipeHP[2],strGrande,256))!=0){
              if ((strstr(strGrande, "jugar"))!=NULL){
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que jugar
                printf("Juega el jugador 3,Se le avisa al jugador 4 que juegue\n");
              }
              else if ((strstr(strGrande, "saltar"))!=NULL){
                printf("Juega el jugador 3, Se le avisa al jugador 1 que juegue,porque el 4 fue saltado\n");
                printf("Juega el jugador 1\n");
              }
              else if ((strstr(strGrande, "+2+4"))!=NULL){
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que robar
                printf("Juega el jugador 3, Se le avisa al jugador 4 que robe\n");
              }
              else if((strstr(strGrande, "reversa"))!=NULL){
                printf("Juega el jugador 3, luego Jugador 2 juega carta por el reversa del Jugador 3\n");
                printf("Se le avisa al jugador 1 que juege\n");
                printf("Juega el jugador 1\n");
              }
              else if ((strstr(strGrande, "jugarR"))!=NULL){
                write(pipePH[1],strGrande,strlen(strGrande));// le mando la señan al jugador 2 que tiene que jugar
                printf("Juega el jugador 3, Se le avisa al jugador 2 que juegue\n");
              }
              else if ((strstr(strGrande, "saltarR"))!=NULL){
                // le mando la señan al jugador 1 que tiene que jugar
                printf("Juega el jugador 3,Se le avisa al jugador 1 que juegue,porque el 2 fue saltado, juega el jugador 1\n");
              }
              else if ((strstr(strGrande, "+2+4R"))!=NULL){
                write(pipePH[1],strGrande,strlen(strGrande));// le mando la señan al jugador 2 que tiene que robar
                printf("Juega el jugador 3,Se le avisa al jugador 2 que robe,\n");
              }
              else if((strstr(strGrande, "reversaR"))!=NULL){
                printf("Juega el jugador 3, luego Jugador 4 juega carta por el reversa del Jugador 3\n");
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que jugar
                printf("Se le avisa al jugador 4 que juege\n");
              }
              else if((strstr(strGrande, "fin"))!=NULL){
                write(pipePH[1],strGrande,strlen(strGrande));//fin
                write(pipePH[5],strGrande,strlen(strGrande));
                wait(NULL);
                printf("Se Acabo el juego\n");
                bucle = 0;
              }
            }
            else if((nbytes = read(pipeHP[4],strGrande,256))!=0){
              if ((strstr(strGrande, "jugar"))!=NULL){
               // le mando la señan al jugador 1 que tiene que jugar
                printf("Juega el jugador 4,Se le avisa al jugador 1 que juegue, Juega el jugador 1\n");
              }
              else if ((strstr(strGrande, "saltar"))!=NULL){
                printf("Juega el jugador 4, Se le avisa al jugador 2 que juegue,porque el 1 fue saltado\n");
                write(pipePH[1],strGrande,strlen(strGrande));
              }
              else if ((strstr(strGrande, "+2+4"))!=NULL){
                write(pipePH[5],strGrande,strlen(strGrande));// le mando la señan al jugador 4 que tiene que robar
                printf("Juega el jugador 4, Se le avisa al jugador 1 que robe, el jugador 1 roba\n");
                printf("Se le avisa al jugador 2 que juegue\n");
                strcpy(strGrande,"jugar");
                write(pipePH[1],strGrande,strlen(strGrande));
              }
              else if((strstr(strGrande, "reversa"))!=NULL){
                printf("Juega el jugador 4, luego Jugador 3 juega carta por el reversa del Jugador 4\n");
                write(pipePH[3],strGrande,strlen(strGrande));
                printf("Se le avisa al jugador 3 que juege\n");
              }
              else if ((strstr(strGrande, "jugarR"))!=NULL){
                write(pipePH[3],strGrande,strlen(strGrande));// le mando la señan al jugador 3 que tiene que jugar
                printf("Juega el jugador 4, Se le avisa al jugador 3 que juegue\n");
              }
              else if ((strstr(strGrande, "saltarR"))!=NULL){
                write(pipePH[1],strGrande,strlen(strGrande));// le mando la señan al jugador 2 que tiene que jugar
                printf("Juega el jugador 4,Se le avisa al jugador 2 que juegue,porque el 3 fue saltado\n");
              }
              else if ((strstr(strGrande, "+2+4R"))!=NULL){
                write(pipePH[3],strGrande,strlen(strGrande));// le mando la señan al jugador 3 que tiene que robar
                printf("Juega el jugador 4,Se le avisa al jugador 3 que robe,\n");
              }
              else if((strstr(strGrande, "reversaR"))!=NULL){
                printf("Juega el jugador 4, luego Jugador 1 juega carta por el reversa del Jugador 4\n");
                printf("Se le avisa al jugador 1 que juege y lo hace \n");
              }
              else if((strstr(strGrande, "fin"))!=NULL){
                write(pipePH[1],strGrande,strlen(strGrande));//fin
                write(pipePH[3],strGrande,strlen(strGrande));
                wait(NULL);
                printf("Se Acabo el juego\n");
                bucle = 0;
              }
            }
            else{
              scanf("Que desea hacer[jugar/fin/jugarR]: %s ",jugada);
              if (strcmp(jugada,"fin")==0){
                write(pipePH[1],jugada,strlen(jugada));
                write(pipePH[3],jugada,strlen(jugada));
                write(pipePH[5],jugada,strlen(jugada));
                wait(NULL);
                printf("Se acabo el juego\n");
                bucle = 0;
              }
              else if (strcmp(jugada,"jugar")==0){
                printf("Ya jugué, soy el 1\n");
                write(pipePH[1],jugada,strlen(jugada));
              }
              else if (strcmp(jugada,"jugarR")==0){
                printf("Ya jugué, soy el 1\n");
                write(pipePH[5],jugada,strlen(jugada));
              }
            }
          }
          priJu =1;
      }
    break;
    case 2: //HIJOS
      close(pipeHP[0]);
      close(pipePH[1]);
      while(bucle){
        bzero(strGrande,256);
        nbytes = read(pipePH[0],strGrande,256);
        if ( strcmp("jugar", strGrande) == 0) {
          printf("Ya jugué, soy el 2\n");
          bzero(strGrande,256);
          scanf("Que desea hacer P2[jugar/fin/jugarR]: %s ",holiwis);
          write(pipeHP[1],strGrande,strlen(strGrande));
        }
        else if (strcmp(strGrande,"jugarR")==0){
          printf("Ya jugué, soy el 2\n");
          bzero(strGrande,256);
          scanf("Que desea hacer P2[jugar/fin/jugarR]: %s ",strGrande);
          write(pipeHP[1],strGrande,strlen(strGrande));
        }
        else if (strcmp(strGrande,"fin")==0){
          write(pipeHP[3],strGrande,strlen(strGrande));
          write(pipeHP[5],strGrande,strlen(strGrande));
          bucle = 0;
          break;
        }
      }
    break;
    case 3:
      close(pipeHP[2]);
      close(pipePH[3]);
        while(bucle){
          bzero(strGrande,256);
          nbytes = read(pipePH[2],strGrande,256);
          if ( strcmp("jugar", strGrande) == 0) {
            printf("Ya jugué, soy el 3\n");
            bzero(strGrande,256);
            scanf("Que desea hacer P3[jugar/fin/jugarR]: %s ",strGrande);
            write(pipeHP[3],strGrande,strlen(strGrande));
          }
          else if (strcmp(strGrande,"jugarR")==0){
            printf("Ya jugué, soy el 3\n");
            bzero(strGrande,256);
            scanf("Que desea hacer P3[jugar/fin/jugarR]: %s ",strGrande);
            write(pipeHP[3],strGrande,strlen(strGrande));
          }
          else if (strcmp(strGrande,"fin")==0){
            write(pipeHP[1],strGrande,strlen(strGrande));
            write(pipeHP[5],strGrande,strlen(strGrande));
            bucle = 0;
            break;
          }
        }
    break;
    case 4:
      close(pipeHP[4]);
      close(pipePH[5]);
      while(bucle){
        bzero(strGrande,256);
        nbytes = read(pipePH[4],strGrande,256);
        if ( strcmp("jugar", strGrande) == 0) {
          printf("Ya jugué, soy el 4\n");
          bzero(strGrande,256);
          scanf("Que desea hacer P4[jugar/fin/jugarR]: %s ",strGrande);
          write(pipeHP[5],strGrande,strlen(strGrande));
        }
        else if (strcmp(strGrande,"jugarR")==0){
          printf("Ya jugué, soy el 4\n");
          bzero(strGrande,256);
          scanf("Que desea hacer P4[jugar/fin/jugarR]: %s ",strGrande);
          write(pipeHP[5],strGrande,strlen(strGrande));
        }
        else if (strcmp(strGrande,"fin")==0){
          write(pipeHP[1],strGrande,strlen(strGrande));
          write(pipeHP[3],strGrande,strlen(strGrande));
          bucle = 0;
          break;
        }
      }
    break;
      }



  // En construccion...

  printf("FIN\n");
  printf("----------------------\n");
  return 0;
}
