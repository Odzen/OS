/*
 * Este programa muestra como leer varias palabras del teclado (stdin)
 * Codigo tomado de: https://www.programiz.com/c-programming/c-strings
 *
 * Modificado por: Juan Sebastian Velasquez  - juan.velasquez.acevedo@correounivalle.edu.co
 *                Mavelyn Sterling Londoño - mavelyn.sterling@correounivalle.edu.co
 * Fecha: 2021-12-16
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <stdlib.h>
#include<stdbool.h>// Booleanos


int main(int argc, char *argv[]) {
  //Un array de tamaño BUFSIZ
  char comando[BUFSIZ];
  //vector de cadena de caracteres
  char **vector;
  //Declaro una variable booleana que me ayudará a saber si el usuario quiere terminar el programa o no
  bool endProgram;
  pid_t pid;

  //Implementacion del While, que termina cuando el usuario digita 'quit'

  while(!endProgram){
    printf("> ");
    //Leo teclado como padre
    leer_de_teclado(BUFSIZ,comando);
    char wordQuit[]="quit";

    vector = de_cadena_a_vector(comando);

    //Seteo la variable booleana, con el resultado de la comparacion entre la entrada del usuario 
    //que se trata como un arreglo multidimensional y wordQuit, que es una string o una arreglo de caracteres.
    endProgram=(vector[0][0]== wordQuit[0]);

    //Hago fork
    pid=fork();

    if(pid<0){
      printf("No pude crear un procesor\n");
      return 2;
    }else if(pid==0){ //El hijo ejecuta el comando
      execvp(vector[0],vector);
    }else{//El papa esperará la ejecución del hijo
      wait(NULL);
    }

  }

  return 0;
}
