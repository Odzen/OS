#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv){
	pid_t pid;
	printf("[%d] Hola mundo\n", getpid());
	pid=fork();
	//Evaluar si el fork me da diferente de 0, para saber que el proceso
	// Se ejecutó, exitosamente
	//Sino, retornar cualquier valor =! de 0, en este caso 2.
	if(pid <0){
		printf("Fallo la instuccion fork()\n");
		return 2;
	}else if(pid==0){//Segmento de hijo
		printf("[%d] Soy el hijo y mi padre es %d\n",getpid(), getppid()); //Si es el hijo =0
	}else{ //Segmento de padre
		printf("[%d] Soy el padre y mi padre es %d\n", getpid(), getppid()); // Retornó pid hijo, >0
		wait(NULL); // No interesa con qué valor sale el hijo, solo quiero bloquearme hasta que mi hijo salga del programa
	}
	//En este print, el primer %d es el id del proceso, y el segundo
	//Lo que devolvio el fork()
	printf("[%d]Hola fork %d\n", getpid(),pid);
	return 0;
}
