#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

int main() {
    long long megabytes_vazados = 0;
    const int TAMANHO_BLOCO_MB = 10;

    printf("Iniciando vazamento de memória ACELERADO...\n");
    printf("Alocando %d MB por iteração, na velocidade máxima.\n", TAMANHO_BLOCO_MB);
    printf("Pressione Ctrl+C para parar a qualquer momento.\n\n");

    while (1) {
        void *memoria = malloc(TAMANHO_BLOCO_MB * 1024 * 1024);

        if (memoria == NULL) {
            printf("\n\n-------------------------------------------------\n");
            printf("FALHA CRÍTICA AO ALOCAR! O sistema ficou sem memória disponível.\n");
            printf("Total vazado antes da falha: %lld MB\n", megabytes_vazados);
            printf("-------------------------------------------------\n");
            break;
        }

        megabytes_vazados += TAMANHO_BLOCO_MB;

        if (megabytes_vazados % 1000 == 0) {
            printf("\rMemória vazada até agora: %lld MB...", megabytes_vazados);
            fflush(stdout);
        }

    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}