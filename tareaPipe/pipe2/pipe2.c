#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0 // Entrada estandar de un proceso valor 0
#define WRITE 1 // Salida estandar de un proceso valor 1

int main() {

  pid_t pid; // Guarda en la variable de tipo pid_t lo que devuelve la llamada al API fork

  int   fd[2]; // Guarda lo que devuelve la llamada al sistema pipe
               // Posicion 0: Entrada estandar. Posicion 1: Salida estandar

  //Vector que guarda los comandos que ejecuta el padre
  char *const vectorDad[]= {"cat","/etc/hosts", NULL};

    //Vector que guarda los comandos que ejecuta el padre
  char *const vectorSon[]= {"sort", NULL};

 
  if (pipe(fd) == -1) { //Si el valor que se devuelve es -1
	perror("Creating pipe"); // es un error
	exit(EXIT_FAILURE);  // Sale de la ejecucion
	}
	
	// Se continua si se vuelve un valor distinto a -1

	//Se usa switch usando como condición lo que devuelve la funcion fork
  switch(pid = fork()) {

  // Si el valor que devuelve pid es 0, es el hijo
  case 0: 

	// Se cierra el descriptor de archivo de escritura
	close(fd[WRITE]); 

	// Interesa leer datos

	// Redireccionar STDIN al descriptor de archivo de lectura.
	dup2(fd[READ], STDIN_FILENO);

	// Ejecutar el vectorSon, con el comando sort
	 execvp(vectorSon[0], vectorSon);

  case -1: // Si el valor que devuelve pid es -1
	perror("fork() failed)"); // es un error
	exit(EXIT_FAILURE);// se sale de la ejecucion

	// si el pid es distinto a 0 y -1
	// se tiene el pid del proceso padre

  default:
	// El proceso padre ejecuta el comando cat /etc/hosts

	// Se cierra el descriptor de archivo de lectura
	close(fd[READ]); // Interesa escribir datos

	// Redireccionar STDOUT al descriptor de archivo de escritura.
	dup2(fd[WRITE], STDOUT_FILENO);

	// Ejecutar el vectorDad, con el comando cat /etc/hosts

	 execvp(vectorDad[0], vectorDad);
  }
}