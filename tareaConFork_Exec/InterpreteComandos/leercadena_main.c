/*
 * Este programa muestra como leer varias palabras del teclado (stdin)
 * Codigo tomado de: https://www.programiz.com/c-programming/c-strings
 *
 * Modificado por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Fecha: 2021-02-26
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <stdlib.h>


int main(int argc, char *argv[]) {
  //Un array de tamaño BUFSIZ
  char comando[BUFSIZ];
  //vector de cadena de caracteres
  char **vector;
  int i;


  pid_t pid;

  //Implementacion del for

  while(1){
    printf("> ");
    //Leo teclado como padre
    leer_de_teclado(BUFSIZ,comando);
    char wordQuit[]="quit";
    const char *quit;
    quit=&wordQuit[0];

    printf( "Quit: %s\n", quit );

      //Hago fork
      pid=fork();

      if(pid<0){
        printf("No pude crear un procesor\n");
        return 2;
      }else if(pid==0){ //El hijo ejecuta el comando
        vector = de_cadena_a_vector(comando);
            printf( "Command: %s\n", vector[0] );

            printf("%d\n", (vector[0][0]== wordQuit[0]));

        if((vector[0][0]== wordQuit[0])){
          printf("Entro");
          exit(-1);
        }else{
          execvp(vector[0],vector);
        }   
      }else{//El papa esperará la ejecución del hijo
          wait(NULL);
      }

  }

  return 0;
}
