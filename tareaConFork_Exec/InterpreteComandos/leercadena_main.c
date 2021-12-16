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
    //Hago fork
    pid=fork();

    if(pid<0){
      printf("No pude crear un procesor\n");
      return 2;
    }else if(pid==0){ //El hijo ejecuta el comando
      vector = de_cadena_a_vector(comando);
      execvp(vector[0],vector);
    }else{//El papa esperará la ejecución del hijo
        wait(NULL);
    }

  }

  return 0;
}
