

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

//funcao executada pelas threads
void *IncrementFunction (int start, int final, int array[]) {
   //log da thread
   printf("Hello World\n");
   for(int i=start; i<final; i++){
      array[i] +=1;
   }
   pthread_exit(NULL);
}

void initializeArray(int array[]){
   for(int i=0; i<4*N; i++){
      array[i] = 0;
   }
}

void printArray(int array[]){
   for(int i=0; i<4*N; i++){
      printf("%d\t", array[i]);
   }
}

//--funcao principal do programa
int main(int argc, char* argv[]) {
   int nthreads = 4;
   int N; //será informado na linha de comando
   int array[4*N];
   //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
   if(argc<2) { 
      printf("--ERRO: informe o valor do de N. <%s> <nthreads>\n", argv[0]); 
      return 1;
   }
   nthreads = atoi(argv[1]);

   //identificadores das threads no sistema
   pthread_t tid_sistema[nthreads]; 
   
   initializeArray(array[4*N]);
   //cria as threads e atribui a tarefa de cada thread
   for(int i=0; i<nthreads; i++) {
      printf("--Cria a thread %d\n", i);
      if (pthread_create(&tid_sistema[i], NULL, IncrementFunction(i*N,i*N-1,array[4*N]), NULL)) {
         printf("--ERRO: pthread_create()\n"); 
         return 2;
      }
   }
/*
n=4
4*n = 16

i*n+4-1

0*4+4=4
1*4+4=8
2*4+4=12
3*4+4=16
*/
   //log da funcao main
   printf("--Thread principal terminou\n");

   pthread_exit(NULL); //necessario para que o processo não seja encerrado antes das threads terminarem
}
