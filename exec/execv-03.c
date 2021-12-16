#include <unistd.h> // execlp()
#include <stdio.h> // perror()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

//Main recibe nada-void
int main()
{
	//Defino vector de char, cons es para que este vector no de pueda modificar
	char *const cmd[]={"/bin/ls", "-l" , NULL};
	execv(cmd[0],cmd);
	perror("Return from execv() not expected");
	exit(EXIT_FAILURE); 
	return 0;
}