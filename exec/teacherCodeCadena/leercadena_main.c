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
#include "leercadena.h"

int main(int argc, char *argv[]) {
  //Un array de tamaño BUFSIZ
  char comando[BUFSIZ];
  //vector de cadena de caracteres
  char **vector;
  int i;


  //printf("Digite su comando ");
  printf("> ");
  //Lee el comando que el usuario digita, usando esta funcion definida en el archivo de cabecera
  leer_de_teclado(BUFSIZ,comando);
  //Imprimir comando por pantalla
  //printf("Comando: ");
  //puts(comando);
  //Transformar ese comando a un vector de cadena de caracteres, donde la útima posición de ese vector es null
  vector = de_cadena_a_vector(comando);
  i = 0;
  while (vector[i]) 
   // printf("%s\n",vector[i++]);
  execvp(vector[0],vector);

  return 0;
}
