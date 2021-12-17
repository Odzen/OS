#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv){
        const int numberProcesses = 5;

	pid_t pid; 
	printf("[%d]Dad proccess, and its dad: %d \n",getpid(), getppid());
	
	// Numero aleatorio diferente de 0, para poder calcular segun la logica dentro del for, solo para el primer ciclo
	pid=1;
        for(int i=0; i<numberProcesses+1;i++){
        	//Si es hijo, entonces imprima, luego de imprimir, entra en break, para que el hijo salga del for, termine su ejecución y continue el padre
		if(pid == 0){
			printf("[%d] Child proccess  number %d, and its dad:%d \n", getpid(), i, getppid());
			break;
		}else{ //Si es padre, crea un nuevo hijo, lo asigna al pid, y espera que se ejecuta ese hijo
			pid= fork();
			wait(NULL);
		}
        }

	return 0;
}
