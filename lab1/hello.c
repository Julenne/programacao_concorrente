/*programacao concorrente: biblioteca pthread*/
/*07-08-2025*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// funcao que as threads executam
void * task (void * arg){
    long int id = (long int) arg;
    printf("Oi arlene, sou a thread %ld\n", id);
    pthread_exit(NULL);
}


int main(int argc, char* argv[]){
    short int nthreads;

    //receber os arg de entrada e valida-los
    if(argc<2){
        printf("ERRO: digite %s <numero threads>\n", argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);

    //criar vetor de identificador de threads
    pthread_t tids[nthreads];

    //criar as threads
    for(long int i=0; i<nthreads;i++){
        if(pthread_create(&tids[i], NULL, task, (void*) i)){
            printf("ERRO:pthread_create da thread %ld\n", i);
            return 2;
        }
    }

    //esperar as threads terminarem antes de imprimir que o programa terminou.(join)
    for(short int i=0; i<nthreads; i++){
        if(pthread_join(tids[i], NULL)){
            printf("ERRO:pthread_create da thread %hd\n", i);
            return 3;
        }
    }

    //finalizar a execução
    puts("Main terminou");

    return 0;

}

//para rodar
//gcc hello.c -o hello -Wall