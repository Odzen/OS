#include <unistd.h> // execlp()
#include <stdio.h> // perror()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

int main(int argc, char const *argv[])
{
	//Funcion generica, se le pasa una aplicacion que se ejecuta normalmente desde la terminal
	// Pero cuando se lleva a cabo el execlp, esa apliación que le pasé como argumento es el nuevo programa-proceso
	//Le paso execlp("app que quiero correr", "app que quiero correr" , "Opción or argumento de la app principal", NULL=Ya no hay más argumentos que quiera pasa ) El primer arg es = al segundo
	printf("Vor a ejecutar 'ls'\n");
	execlp("ls","ls","-l", NULL);
	printf("Fin ejecucion 'ls'\n");
	perror("Return from execlp() not expected");
	exit(EXIT_FAILURE);
	return 0;
}