//"Hello world" concorrente usando a biblioteca pthread de C

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define T 4

int *vetor;
int n;

//funcao executada pela thread
void * incrementa1(void *arg) {
    int thread_id = *((int*)arg);
    int inicio = thread_id * n;
    int fim = inicio + n;

    for (int i = inicio; i < fim; i++) {
        vetor[i] += 1;
    }

    pthread_exit(NULL);
}	

//funcao principal
int main(int argc, char* argv[]) {
   //variaveis do programa
   pthread_t *tid; //vetor para guardar os identificadores das threads no sistema
   //verificar argumentos de entrada
   if(argc < 2 ) {
      printf("ERRO de entrada de parametros: Digite %s <numero de threads>\n", argv[0]);
      return 1;
   }
   //armazenar o numero de threads
   n = atoi(argv[1]);
   n = n *4;

   vetor = (int *) malloc(n * sizeof(int));
   for(int i = 0; i<n; i++){
        vetor[i] = rand() % 10;
        printf("%d", vetor[i]);
   }
   printf("\n");

   //criar os fluxos de execução (threads)
   tid = malloc(4 *sizeof(pthread_t));
   int threads_ids[4];

   for(long int i=0; i<4; i++) {
    threads_ids[i] = i;
      //cria a thread     
      int ret = pthread_create(&tid[i], NULL, incrementa1, &threads_ids[i]);
      if(ret) { //retorna 0 quando ocorre com sucesso e diferente de 0 caso contrario
         printf("ERRO %d na criacao da thread %ld\n", ret, i);
         return 3;
      }   
   }	   

   //esperar os fluxos terminarem suas execucoes
   for(int i=0; i<4; i++) {
      int ret = pthread_join(tid[i], NULL);
      if(ret) { //retorna 0 quando ocorre com sucesso e diferente de 0 caso contrario
         printf("ERRO %d na espera da thread %d\n", ret, i);
         return 4;
      }   
   }

   for(int i = 0; i < n; i++){
    printf("%d", vetor[i]);
   }
   
   free(vetor);
   //finalizar o programa
   return 0;
}