#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//funcao executada pelas threads

void* alo_thread(void* arg){
    long int id = (long int) arg;
    printf("Alo mundo da thread %ld\n", arg);
    pthread_exit(NULL);
}



//funcao principal
int main(int argc, char* argv[]) {
    //declarar variaveis
    int nthreads;
    pthread_t *tid;

    //receber argumentos
    if(argc < 2) {
        printf("ERRO de entrada: digite: %s <numero de threads>\n", argv[0]);

        return 1;
    }

    //iniciar as variaveis
    nthreads = atoi(argv[1]);
    tid = malloc(nthreads*sizeof(pthread_t));
    if(tid == NULL) {
        printf("ERRO de alocação de memoria\n");

        return 1;
    }

    //criar as threads
    for(long int i=0; i<nthreads; i++) {
        pthread_create(&tid[i], NULL, alo_thread,(void*)i); 
    }

    //esperar as threads terminarem
    for(long int i=0; i<nthreads; i++){
        pthread_join(tid[i], NULL);
    }

    //finalizar o programa
    printf("FIM\n");
    return 0;
}