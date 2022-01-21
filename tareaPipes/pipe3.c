#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h> 
#include<assert.h>


//#define READ  0 // Entrada estandar de un proceso valor 0
//#define WRITE 1 // Salida estandar de un proceso valor 1

int main() {

  pid_t pid; // Guarda en la variable de tipo pid_t lo que devuelve la llamada al API fork

  //int   fd[2]; // Guarda lo que devuelve la llamada al sistema pipe
               // Posicion 0: Entrada estandar. Posicion 1: Salida estandar

  int fd,fd2,sz,sz2,numero_random;

  //int numero_random,num;

  char *archivo= "archivo.txt";

  //FILE *fd;
  //FILE *fd2;


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

  close(fd);

  int fd2 = open("file2.txt", O_RDONLY | O_CREAT);

	printf("fd hijo: %d \n", fd2);
	printf("fd padre: %d \n", fd);

  dup2(fd2,fd);

  //write(fd, &numero_random, sizeof(numero_random));
  
  


  assert(fd2 >= 0);


	//if (fd2 < 0) { perror("No se pudo cerrar el archivo"); exit(1); } 

	//int sz= read(fd, c, 10); 

	
  /*
  fd2= fopen(archivo,"r");

  if(fd==NULL){
  	fprintf(stderr, "Archivo no encontrado en hijo\n");
  }
  printf(fd2);
	
	*/


  printf("Entra al hijo paso open\n");

  /*
	while(getw(fd)!=EOF)
   {	
   		   printf("Entra while hijo\n");

      num= getw(fd);
      printf("Numero random leido es: %d \n", num);
   }
   fclose(fd);
   */
   printf("Entra al hijo paso todo\n");

   /*
   if (close(fd2) < 0) 
	{ 
	  perror("No se pudo cerrar el archivo fd2\n"); 
	  exit(1); 
	}
	printf("closed the fd.\n");
	*/

   break;


  case -1: // Si el valor que devuelve pid es -1
  printf("Entra al fork\n");
  printf("fd hijo: %d \n", fd2);
  printf("fd padre: %d \n", fd);
	perror("fork() failed)"); // es un error
	exit(EXIT_FAILURE);// se sale de la ejecucion

	// si el pid es distinto a 0 y -1
	// se tiene el pid del proceso padre

  default:

  	

  	printf("Entra al padre\n");


  	close(fd2);



  	fd = open("file1.txt",   O_CREAT | O_WRONLY);


  	printf("fd hijo: %d \n", fd2);
		printf("fd padre: %d \n", fd);


		srand(time(NULL));
  	numero_random = rand() % 1000 + 1;

  	printf("Numero random creado es: %d \n", numero_random);

  	dup2(fd,1);

  	printf("%d",numero_random);

  	//write(fd, &numero_random, sizeof(numero_random));
  	


  	//fd= fopen(archivo,"w");
  	assert(fd >= 0);

  	break;
  	//close(fd);

  	/*
  	if (close(fd) < 0) 
		{ 
	  perror("No se pudo cerrar el archivo fd\n"); 
	  exit(1); 
		}
		*/

  	//if(fd==NULL){
  		//fprintf(stderr, "Archivo no encontrado en padre\n");
  		//exit(2);
  	//}

  	//putw(numero_random,fd);

  	//fclose(fd);


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

  return 0;
}
