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
#include <sys/mman.h>

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

void SacarCartas(char* jugador, int cartas_a_sacar){
  int total = ContarMazo("Mazo");

  while(cartas_a_sacar > 0){
    srand(time(NULL));
    int temp = rand()%(total+1);
    char card[15];

    obtenerNombre(temp,card,"Mazo");
    MoveFile("Mazo/",jugador,card);
    cartas_a_sacar--;
  }
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
  void* shmem = create_shared_memory(128);

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
        //char jugada[60];
        if (priJu==0){
            printf("Empieza el player 1\n");
            int eleccion = ChooseFile("Jugador1");
            if(eleccion == -1){
              SacarCartas("Jugador1/",1);
            }
            else{
              char cardd[15];
              obtenerNombre(eleccion,cardd,"Jugador1");
              MoveFile("Jugador1/","EnJuego/",cardd);
              printf("Player 1 jugó un %s\n",cardd);
              if (strstr(cardd,"reversa")!=NULL){
                bzero(strGrande,256);
                strcpy(strGrande,"jugarR");
                printf("Se le comunica al jugador 4 su turno\n");
                memcpy(shmem, "41", sizeof("41"));
                write(pipePH[5],strGrande,strlen(strGrande));
                sleep(10);
              }
              else{
                bzero(strGrande,256);
                strcpy(strGrande,"jugar");
                printf("Se le comunica al jugador 2 su turno\n");
                //char* num = "21";
                memcpy(shmem, "21", sizeof("21"));
                //printf("%s\n",shmem);
                write(pipePH[1],strGrande,strlen(strGrande));
                sleep(10);
              }
          }

      }
      else{

        bzero(strGrande,256);
        //char turno[2];
        //strcpy(turno,shmem);
        if (((char*)shmem)[0]=='1'){ //voy al 1

          int R;// de donde debo leer
          if(((char*)shmem)[1]=='3'){//vengo del 3
            R = 2;
          }
          else if(((char*)shmem)[1]=='4'){//vengo del 4
            R = 4;
          }
          else if(((char*)shmem)[1]=='2'){//vengo del 2
            R = 0;
          }
          bzero(strGrande,256);
          nbytes = read(pipeHP[R],strGrande,256);
          if (strstr(strGrande,"jugar")!=NULL){
            printf("Se le comunica al jugador 1 su turno\n");
            int eleccion = ChooseFile("Jugador1");
            if(eleccion == -1){
              SacarCartas("Jugador1/",1);
            }
            else{
              char cardd[15];
              obtenerNombre(eleccion,cardd,"Jugador1");
              MoveFile("Jugador1/","EnJuego/",cardd);
              printf("Player 1 jugó un %s\n",cardd);
              if (strcmp(strGrande,"jugar")==0){
                if (strstr(cardd,"reversa")!=NULL){
                  bzero(strGrande,256);
                  strcpy(strGrande,"jugarR");
                  memcpy(shmem, "4", sizeof("4"));
                  printf("Se le comunica al jugador 4 su turno\n");
                }
                else{
                  bzero(strGrande,256);
                  strcpy(strGrande,"jugar");
                  memcpy(shmem, "2", sizeof("2"));
                  printf("Se le comunica al jugador 2 su turno\n");
                }
              }
              else{
                if (strstr(cardd,"reversa")!=NULL){
                  bzero(strGrande,256);
                  strcpy(strGrande,"jugar");
                  printf("Se le comunica al jugador 2 su turno\n");
                  memcpy(shmem, "2", sizeof("2"));
                }
                else{
                  bzero(strGrande,256);
                  strcpy(strGrande,"jugar");
                  memcpy(shmem, "4", sizeof("4"));
                  printf("Se le comunica al jugador 4 su turno\n");
                }
              }
            }
          }
        }

        else if (((char*)shmem)[0]=='2'){ //voy al 2
          int R;// de donde debo leer

          if(((char*)shmem)[1]=='3'){
            R = 2;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 2 su turno\n");
              write(pipePH[1],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else if(((char*)shmem)[1]=='4'){
            R = 4;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 2 su turno\n");
              write(pipePH[1],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else{ //Si vengo del 1
            printf("Se le comunica al jugador 2 su turno\n");
            //printf("HOLA\n");
            write(pipePH[1],strGrande,strlen(strGrande));
            sleep(10);
          }
          //else{ // por agregar mas reglas (skip, robar) no actualizado
            //printf("Jugador 2 finalizo el juego.\nSe acabo el juego\n");
            //strcpy(jugada,"fin");
            //write(pipePH[1],jugada,strlen(jugada));
            //write(pipePH[3],jugada,strlen(jugada));
            //write(pipePH[5],jugada,strlen(jugada));
            //wait(NULL);
            //bucle = 0;
            //break;
          //}
        }
        else if(((char*)shmem)[0]=='3'){//voy al 3
          int R;// de donde debo leer

          if(((char*)shmem)[1]=='2'){
            R = 0;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 3 su turno\n");
              write(pipePH[3],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else if(((char*)shmem)[1]=='4'){
            R = 4;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 3 su turno\n");
              write(pipePH[3],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else{ //Si vengo del 1
            printf("Se le comunica al jugador 3 su turno\n");
            write(pipePH[3],strGrande,strlen(strGrande));
            sleep(10);
          }
        }

        else if(((char*)shmem)[0]=='4'){
          int R;// de donde debo leer
          if(((char*)shmem)[1]=='2'){
            R = 0;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 4 su turno\n");
              write(pipePH[5],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else if(((char*)shmem)[1]=='3'){
            R = 2;
            bzero(strGrande,256);
            nbytes = read(pipeHP[R],strGrande,256);
            if (strstr(strGrande,"jugar")!=NULL){
              printf("Se le comunica al jugador 4 su turno\n");
              write(pipePH[5],strGrande,strlen(strGrande));
              sleep(10);
            }
          }
          else{ //Si vengo del 1
            printf("Se le comunica al jugador 4 su turno\n");
            write(pipePH[5],strGrande,strlen(strGrande));
            sleep(10);
          }
        }
      }
      priJu =1;
    }


    break;
    case 2: //HIJOS
      close(pipeHP[0]);
      close(pipePH[1]);
      while(bucle==1){
        bzero(strGrande,256);
        nbytes = read(pipePH[0],strGrande,256);
        if ( strcmp("jugar", strGrande) == 0) {
          printf("Voy a jugar, soy el 2\n");
          int eleccion = ChooseFile("Jugador2");
          if(eleccion == -1){
              SacarCartas("Jugador2/",1);
          }
          else{
            char cardd[15];
            obtenerNombre(eleccion,cardd,"Jugador2");
            MoveFile("Jugador2/","EnJuego/",cardd);
            printf("Player 2 jugó un %s\n",cardd);
            if (strstr(cardd,"reversa")!=NULL){
              bzero(strGrande,256);
              strcpy(strGrande,"jugarR");
              memcpy(shmem, "12", sizeof("12"));
              write(pipeHP[1],strGrande,strlen(strGrande));

            }
            else{//SI NO ES REVERSA
              bzero(strGrande,256);
              strcpy(strGrande,"jugar");
              memcpy(shmem, "32", sizeof("32"));
              //juega el 3 vengo del 2
              write(pipeHP[1],strGrande,strlen(strGrande));

            }
          }
        }
        else if(strcmp("jugarR",strGrande)==0){
          printf("Voy a jugar, soy el 2\n");
          int eleccion = ChooseFile("Jugador2");
          if(eleccion == -1){
              SacarCartas("Jugador2/",1);
          }
          else{
            char cardd[15];
            obtenerNombre(eleccion,cardd,"Jugador2");
            MoveFile("Jugador2/","EnJuego/",cardd);
            printf("Player 2 jugó un %s\n",cardd);
            if (strstr(cardd,"reversa")!=NULL){
              bzero(strGrande,256);
              strcpy(strGrande,"jugar");
              memcpy(shmem, "32", sizeof("32")); // juega el 3 y viene del 2
              write(pipeHP[1],strGrande,strlen(strGrande));
            }
            else{//SI NO ES REVERSA
              bzero(strGrande,256);
              strcpy(strGrande,"jugarR");
              memcpy(shmem, "12", sizeof("12")); //juega el 1 viene del 2
              write(pipeHP[1],strGrande,strlen(strGrande));
            }
          }
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
           printf("Voy a jugar, soy el 3\n");
           int eleccion = ChooseFile("Jugador3");
           if(eleccion == -1){
               SacarCartas("Jugador3/",1);
           }
           else{
             char cardd[15];
             obtenerNombre(eleccion,cardd,"Jugador3");
             MoveFile("Jugador3/","EnJuego/",cardd);
             printf("Player 3 jugó un %s\n",cardd);
             if (strstr(cardd,"reversa")!=NULL){
               bzero(strGrande,256);
               strcpy(strGrande,"jugarR");
               memcpy(shmem, "23", sizeof("23"));
               write(pipeHP[3],strGrande,strlen(strGrande));
             }
             else{//SI NO ES REVERSA
               bzero(strGrande,256);
               strcpy(strGrande,"jugar");
               memcpy(shmem, "43", sizeof("43"));
               write(pipeHP[3],strGrande,strlen(strGrande));
             }
           }
         }
         else if(strcmp("jugarR",strGrande)==0){
           printf("Voy a jugar, soy el 3\n");
           int eleccion = ChooseFile("Jugador3");
           if(eleccion == -1){
               SacarCartas("Jugador3/",1);
           }
           else{
             char cardd[15];
             obtenerNombre(eleccion,cardd,"Jugador3");
             MoveFile("Jugador3/","EnJuego/",cardd);
             printf("Player 3 jugó un %s\n",cardd);
             if (strstr(cardd,"reversa")!=NULL){
               bzero(strGrande,256);
               strcpy(strGrande,"jugar");
               memcpy(shmem, "43", sizeof("43")); // juega el 3 y viene del 2
               write(pipeHP[3],strGrande,strlen(strGrande));
             }
             else{//SI NO ES REVERSA
               bzero(strGrande,256);
               strcpy(strGrande,"jugarR");
               memcpy(shmem, "23", sizeof("23")); //juega el 1 viene del 2
               write(pipeHP[3],strGrande,strlen(strGrande));
             }
           }
         }
       }
      break;
      case 4://HIJOS
        close(pipeHP[4]);
        close(pipePH[5]);
        while(bucle==1){
          bzero(strGrande,256);
          //printf("HOLA\n");
          nbytes = read(pipePH[4],strGrande,256);
          //printf("HOLA2\n");
          if ( strcmp("jugar", strGrande) == 0) {
            printf("Voy a jugar, soy el 4\n");
            int eleccion = ChooseFile("Jugador4");
            if(eleccion == -1){
                SacarCartas("Jugador4/",1);
            }
            else{
              char cardd[15];
              obtenerNombre(eleccion,cardd,"Jugador4");
              MoveFile("Jugador4/","EnJuego/",cardd);
              printf("Player 4 jugó un %s\n",cardd);
              if (strstr(cardd,"reversa")!=NULL){
                bzero(strGrande,256);
                strcpy(strGrande,"jugarR");
                memcpy(shmem, "34", sizeof("34"));
                write(pipeHP[5],strGrande,strlen(strGrande));
              }
              else{//SI NO ES REVERSA
                bzero(strGrande,256);
                strcpy(strGrande,"jugar");
                memcpy(shmem, "14", sizeof("14"));
                write(pipeHP[5],strGrande,strlen(strGrande));
              }
            }
          }
          else if(strcmp("jugarR",strGrande)==0){
            printf("Voy a jugar, soy el 4\n");
            int eleccion = ChooseFile("Jugador4");
            if(eleccion == -1){
                SacarCartas("Jugador4/",1);
            }
            else{
              char cardd[15];
              obtenerNombre(eleccion,cardd,"Jugador4");
              MoveFile("Jugador4/","EnJuego/",cardd);
              printf("Player 4 jugó un %s\n",cardd);
              if (strstr(cardd,"reversa")!=NULL){
                bzero(strGrande,256);
                strcpy(strGrande,"jugar");
                memcpy(shmem, "14", sizeof("14")); // juega el 3 y viene del 2
                write(pipeHP[5],strGrande,strlen(strGrande));
              }
              else{//SI NO ES REVERSA
                bzero(strGrande,256);
                strcpy(strGrande,"jugarR");
                memcpy(shmem, "34", sizeof("34")); //juega el 1 viene del 2
                write(pipeHP[5],strGrande,strlen(strGrande));
              }
            }
          }
        }
       break;
    }
  // En construccion...
  printf("----------------------\n");
  return 0;
}
