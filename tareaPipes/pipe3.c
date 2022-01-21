#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>


//#define READ  0 // Entrada estandar de un proceso valor 0
//#define WRITE 1 // Salida estandar de un proceso valor 1

int main() {

  pid_t pid; // Guarda en la variable de tipo pid_t lo que devuelve la llamada al API fork

  //int   fd[2]; // Guarda lo que devuelve la llamada al sistema pipe
               // Posicion 0: Entrada estandar. Posicion 1: Salida estandar

  //int fd,sz,sz2,numero_random;

  int numero_random,num;

  char *archivo= "archivo.txt";

  FILE *fd;


 	/*
  if (pipe(fd) == -1) { //Si el valor que se devuelve es -1
	perror("Creating pipe"); // es un error
	exit(EXIT_FAILURE);  // Sale de la ejecucion
	}
	*/
	
	// Se continua si se vuelve un valor distinto a -1

	//Se usa switch usando como condición lo que devuelve la funcion fork
  switch(pid = fork()) {

  // Si el valor que devuelve pid es 0, es el hijo
  case 0: 

  printf("Entra al hijo\n");


  //int fd = open("file.txt", O_RDONLY);


	//if (fd < 0) { perror("No se pudo cerrar el archivo"); exit(1); } 

	//int sz= read(fd, c, 10); 

  fd= fopen(archivo,"r");

  if(fd==NULL){
  	fprintf(stderr, "Archivo no encontrado en hijo\n");
  }


	while(getw(fd)!=EOF)
   {
      num= getw(fd);
      printf("Numero random leido es: %d \n", num);
   }
   fclose(fd);

   /*
   if (close(fd) < 0) 
	{ 
	  perror("No se pudo cerrar el archivo"); 
	  exit(1); 
	}
	printf("closed the fd.\n");
	*/


  case -1: // Si el valor que devuelve pid es -1
	perror("fork() failed)"); // es un error
	exit(EXIT_FAILURE);// se sale de la ejecucion

	// si el pid es distinto a 0 y -1
	// se tiene el pid del proceso padre

  default:

  	printf("Entra al padre\n");
		srand(time(NULL));
  	numero_random = rand() % 1000 + 1;

  	printf("Numero random creado es: %d \n", numero_random);
  	//fd = open("file.txt", O_WRONLY | O_CREAT | O_EXCL);


  	fd= fopen(archivo,"w");

  	if(fd==NULL){
  		fprintf(stderr, "Archivo no encontrado en padre\n");
  		exit(2);
  	}

  	putw(numero_random,fd);

  	fclose(fd);


  	/*if (fd ==-1) 
    {
    	perror("Cannot open the file");
    	exit(2);                 
    }

    printf("opened the fd = % d\n", fd); 


    sz2 = write(fd, 1000, strlen("hello geeks\n")); 
    */

  // Se cierra el descriptor de archivo de lectura
	//close(fd[READ]); // Interesa escribir datos

	// Redireccionar STDOUT al descriptor de archivo de escritura.
	//dup2(fd[WRITE], STDOUT_FILENO);

	// Redireccionar STDOUT al descriptor de archivo de escritura.
	// dup2(fd[WRITE], STDOUT_FILENO);


  }
}
