#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int main(){

     int fd[2];
     char buffer[30];
     pid_t pid;


     pipe(fd); // Se crea el PIPE
     pid = fork();
     int numero_random;
     switch(pid){
     
          case -1: // Error
                printf("No se ha podido crear un hijo \n");
                exit(-1);
                break;
          case 0: // Hijo
                close(fd[1]); // Cierra el descriptor de escritura
                read(fd[0], buffer, sizeof(numero_random));
                numero_random=*(int*)buffer;
                printf("Mensaje leido por el hijo: %d \n", numero_random);
                if(numero_random>=500){printf("mayor o igual a 500\n");}
                  else{printf("menor que 500\n");}
                break;
          default: // Padre
                close(fd[0]); // Cierra el descriptor de lectura
                srand(time(NULL));
                numero_random = rand() % 1000 + 1;
                printf("El padre escribe en el pipe un numero random: %d\n", numero_random);
                write(fd[1], (char*)&numero_random, sizeof(numero_random));
     }
}