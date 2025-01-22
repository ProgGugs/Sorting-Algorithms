#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <cstdlib>
# include <sys/time.h>

// BubbleSort
void bubbleSort(int x, int vet[], int tamanho) 
{
    int aux = 0;
    while (x>=0) {

        // O "for" percorre todo o vetor comparando cada numero com o outro que está na posição seguinte 
        for (int i=0;i<tamanho-1;i++) {

            // Se o numero é maior que do que o que está na posição seguinte, seus valores são trocados
            if (vet[i]>vet[i+1]) {
                int var = vet[i+1];
                vet[i+1] = vet[i];
                vet[i] = var;
                aux++;
            }
        }

        // Quando não houver nenhuma troca depois de percorrer todo o vetor quantas vezes for necessário
        // quer dizer que o vetor já está ordenado!
        // e a variável "x" se torna negativa para que o "while" pare de ser executado
        if(aux == 0) {
            x = -1;
        }
        aux = 0;
    }
    return;
}

// Função para impressão de um "array" qualquer
void imprimirArray(int array[], int tamanho) {
    for(int i=0;i<tamanho;i++) {
        printf("%i ", array[i]);
    }
    printf("\n");
    return;
} 

// Função para troca de valores entre duas posições de memória
void troca(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

// Função que ordena a partir de um pivo
int separaPivo(int array[], int minimo, int maximo) {

    // O pivo originalmente é definido como o último número do vetor
    int valor_pivo = array[maximo];
    int j = minimo;

    // Loop que coloca todos os números menores ou iguais ao pivo a esquerda do vetor
    // trocando de posição com os que são maiores que o pivo
    for (int i = minimo; i < maximo; i++) {
        if(array[i] <= valor_pivo) {
            troca(&array[j], &array[i]);
            j++;
        }
    }

    // Troca o indice do pivo para a posição exatamente no meio 
    // dos números maiores que ele (a direita) e menores ou iguais a ele (a esquerda)
    troca(&array[j], &array[maximo]);

    // Retorna o indice do pivo
    return j;
}

// QuickSort
void quickSortRecursivo(int array[], int minimo , int maximo) {

    // Coleta o indice do pivo a partir da função "separaPivo"
    int indice_pivo = separaPivo(array, minimo, maximo);

    // Condição de parada, caso a última chamada da função 
    // seja um "array" de posições minima e máxima iguais
    if (minimo < maximo) {

        // Chamadas recursivas
        quickSortRecursivo(array, minimo, indice_pivo - 1);
        quickSortRecursivo(array, indice_pivo, maximo);
    }
    return;
}

// Função do QuickSort que apenas redireciona para recursividade do algoritmo
void quickSort(int array[], int tamanho) {
    quickSortRecursivo(array, 0, tamanho - 1);
    return;
}

int main()
{
    int vet[100000];
    int vet_bubble[100000];
    int vet_quick[100000];

    // Gerando um vetor aleatório de 10000 posições
    srand(time(NULL));
    for (int i = 0 ; i < 10000; i++) {
    vet[i] = rand() % 100;
    }

    // Imprimindo o vetor gerado no "Terminal" 
    // e passando ele para outros dois vetores de controle (um para o bubble outro para o quick)
    printf("VETOR GERADO: \n");
    for (int v = 0; v < 10000; v++) {
        vet_bubble[v] = vet[v];
        vet_quick[v] = vet[v];
        printf(" %i ", vet[v]);
    }
    int tamanho = 10000;
    
    // Estrutura para registro do tempo de execução de cada algoritmo
    struct timeval tvalBS_Inicio, tvalBS_Fim,
                   tvalQS_Inicio, tvalQS_Fim;
    
    //1º: Monitorando o tempo de execução do BubbleSort
    printf("\nBubble Sort\n\n");
    printf("- Início\n");
    gettimeofday (&tvalBS_Inicio, NULL);
    bubbleSort(0,vet_bubble, tamanho);

    // Imprimindo o vetor ordenado por BubbleSort
    printf("Vetor Ordenado por BubbleSort:\n");
    imprimirArray(vet_bubble, tamanho);

    printf("- Fim\n");
    gettimeofday (&tvalBS_Fim, NULL);

    printf("\n\n\n");

    //2º: Monitorando o tempo de execução do QuickSort
    printf("Quick Sort\n\n");
    printf("- Início\n");
    gettimeofday (&tvalQS_Inicio, NULL);
    quickSort(vet_quick, tamanho);

    // Imprimindo o vetor ordenado por QuickSort
    printf("Vetor Ordenado por QuickSort:\n");
    imprimirArray(vet_quick, tamanho);

    printf("- Fim\n");
    gettimeofday (&tvalQS_Fim, NULL);

    //3º: Mostrando os resultados de cada um dos algoritmos de ordenação
    printf ("Tempo Total\n");
    printf ("Bubble Sort = %.3f segundos\n",
    (double) (tvalBS_Fim.tv_usec - tvalBS_Inicio.tv_usec) / 1000000 +
    (double) (tvalBS_Fim.tv_sec - tvalBS_Inicio.tv_sec));
    printf ("Quick Sort = %.3f segundos\n",
    (double) (tvalQS_Fim.tv_usec - tvalQS_Inicio.tv_usec) / 1000000 +
    (double) (tvalQS_Fim.tv_sec - tvalQS_Inicio.tv_sec));
    return 0;

}