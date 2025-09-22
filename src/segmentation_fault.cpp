#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Esta função será o nosso "tratamento de erro"
// Ela será chamada quando o sinal SIGSEGV for recebido
void sigsegv_handler(int signum) {
    printf("!!! ERRO: Segmentation Fault !!!\n");
    printf("   Sinal número: %d\n", signum);
    printf("   Causa provável: Acesso a um ponteiro nulo ou memória inválida.\n");
    printf("============================================\n");
    
    exit(1);
}

void causa_o_erro() {
    int *p = NULL;
    printf("Antes de causar o segmentation fault...\n");
    printf("Valor: %d\n", *p); 
}

int main() {
    // Registra a nossa função 'sigsegv_handler' para ser chamada
    // sempre que um sinal SIGSEGV ocorrer.
    signal(SIGSEGV, sigsegv_handler);

    printf("Programa iniciado. Tentando causar o erro...\n");
    causa_o_erro();

    return 0;
}