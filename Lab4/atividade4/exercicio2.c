#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>
#include <time.h>

long int cont = 0; //variavel compartilhada entre as threads
long long int N = 0; //variavel compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua
long int numeroAtual = 1;

int ehPrimo(long long int n) {
    int i;
    if (n<=1) return 0;
    if (n==2) return 1;
    if (n%2==0) return 0;
    for (i=3; i<sqrt(n)+1; i+=2)
        if(n%i==0) return 0;

    return 1;
}

void *ExecutaTarefa (void *arg) {
    long int id = (long int) arg;
    long int n;
    printf("Thread : %ld esta executando...\n", id);

    while (1) {
        pthread_mutex_lock(&mutex); // inicio da seção critica
        n = numeroAtual++; //seção critica
        pthread_mutex_unlock(&mutex); // fim da seção critica
        
        if(n > N){
            break;
        }

        if (ehPrimo(n)) {
            pthread_mutex_lock(&mutex); // inicio da seção critica
            cont++; //seção critica
            pthread_mutex_unlock(&mutex); // fim da seção critica
        }
    }

    printf("Thread : %ld terminou!\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t *tid;
    int nthreads;
    double inicio, fim;

    if(argc<3) {
        printf("Digite: %s <numero de elementos> <numero de threads>\n", argv[0]);
        return 1;
    }
    N = atoll(argv[1]);
    nthreads = atoi(argv[2]);

    tid = (pthread_t*) malloc(sizeof(pthread_t)*(nthreads+1));
    if(tid==NULL) {puts("ERRO--malloc"); return 2;}


    //marca o tempo de inicio do programa
    inicio = clock();

    //inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    for(long int t=0; t<nthreads; t++) {
        if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)t)) {
        printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }

    for (int t=0; t<nthreads; t++) {
        if (pthread_join(tid[t], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    } 
    //finaliza o mutex
    pthread_mutex_destroy(&mutex);

    //marca o tempo do fim do programa
    fim = clock();
   
    printf("Quantidade de primos = %ld\n", cont);
    printf("Tempo de execução = %0.8f\n", (fim-inicio) / CLOCKS_PER_SEC);

    free(tid);

    return 0;
}