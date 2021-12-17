#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(void) {
	pid_t bash = getppid();//PID de la terminal
	pid_t pmain = getpid();//PID del proceso main
	printf("proceso padre[%d] - proceso main[%d]\n",bash,pmain);
	int i=0;
	pid_t rc; // el PID para el fork
	while(i<5){ 
		rc = fork(); // Se crea una copia del proceso
		if(rc<0){ // cuando no hay proceso
			fprintf(stderr,"No se creó el proceso\n");
			exit(1);
		}else if(rc==0){
			//Codigo ejecutado por cada proceso hijo
			printf("El hijo[%d] - El padre es[%d]\n",getpid(), pmain); // Se imprime el padre y el hijo con el PID
			return 0;
		}else{
			wait(NULL);
		}
		i++;
	}
  return 0;
}