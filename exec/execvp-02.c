#include <unistd.h> // execlp()
#include <stdio.h> // perror()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

//Main recibe void
int main(void)
{
	//Defino vector de char, cons es para que este vector no de pueda modificar
	char *const cmd[]={"ls", "-l" , NULL};
	//Siempre paso 2 argumentos, el primero es un cadena de caracteres, y el segundo es un vector
	//v= vector, p=path, execvp
	//cmd[0] hace referencia al "ls", cmd= Hacer referencia a todo el vector
	//Funciona igual que el execlp, pero aquí el vector se puede construir dinámicamente, podría asignar otros valores
	//En el execlp, lo que escribi antes de compilar, es lo que me va a quedar. No tengo flexibilidad
	execvp(cmd[0],cmd);
	perror("Return from execvp() not expected");
	exit(EXIT_FAILURE); 
	return 0;
}