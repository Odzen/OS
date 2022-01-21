#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0 // Entrada estandar de un proceso valor 0
#define WRITE 1 // Salida estandar de un proceso valor 1

int main() {

  pid_t pid; // Guarda lo que devuelve la llamada al sistema fork
  int   fd[2]; // Guarda lo que devuelve la llamada al sistema pipe
               // Posicion 0: Entrada estandar. Posicion 1: Salida estandar
 
  if (pipe(fd) == -1) { //Si el valor que se devuelve es -1
	perror("Creating pipe"); // es un error
	exit(EXIT_FAILURE);  // Sale de la ejecucion
	}
// Se continua si se vuelve un valor distinto a -1

  switch(pid = fork()) { // Menu para llamar la funcion fork

  case 0: // Si el valor que devuelve pid es 0
          // El nuevo proceso ejecutara lo siguiente:

	// The child process will execute wc.
	// Close the pipe write descriptor.
	close(fd[WRITE]); // Interesa leer datos

	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);

	// Execute wc
	// reemplaza el codigo del proceso por wc
	execlp("wc", "wc", NULL);

  case -1: // Si el valor que devuelve pid es -1
	perror("fork() failed)"); // es un error
	exit(EXIT_FAILURE);// se sale de la ejecucion

// si el pid es distinto a 0 y -1
// se tiene el pid del proceso padre

  default:
	// The parent process will execute ls.
	// Close the pipe read descriptor.
	close(fd[READ]); // Interesa escribir datos

	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);

	// Execute ls -l
	// reemplaza el codigo del proceso por ls
	execlp("ls", "ls", NULL);
  }
}