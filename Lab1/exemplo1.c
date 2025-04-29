#include <stdio.h>
#include <stdlib.h>

void incrementa (int *p, int n, int t);

int main(){
    int N;
    printf("Digite o tamanho que deseja que o vetor tenha: ");
    scanf("%d", &N);

    int *vet1;
    vet1 = (int *) malloc(N * sizeof(int));

    for(int i = 0; i < N; i++){
        vet1[i] = rand() % 10;
        printf("%d\n", vet1[i]);
    }

    int t;
    printf("Digite o quanto deseja incrementar em cada posição:");
    scanf("%d", &t);

    incrementa(vet1, N, t);

    return 0;
}






void incrementa (int *p, int n, int t){
    for(int i = 0; i < n; i++){
        p[i] = p[i] + t;
        printf("%d", p[i]);
    }

}