#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cstring> // Para memset

// Buffer para nossa pilha de emergência.
// SIGSTKSZ é uma constante que define um tamanho mínimo seguro para a pilha alternativa.
static char* alternate_stack = new char[SIGSTKSZ];

void sigsegv_handler(int signum) {
    // Esta mensagem agora será impressa, pois o handler está rodando na pilha de emergência!
    std::cout << "\n\n--- ERRO CRÍTICO DETECTADO (EM MODO DE SEGURANÇA) ---" << std::endl;
    std::cout << "Descrição: Falha de segmentação (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: STACK OVERFLOW (Estouro da Pilha de Chamadas)." << std::endl;
    std::cout << "O handler foi executado em uma pilha alternativa, pois a principal esgotou." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    exit(signum);
}

void causar_stackoverflow(long long contador) {
    std::cout << "\rProfundidade da recursão: " << contador << std::flush;
    causar_stackoverflow(contador + 1);
}

int main() {
    // --- Configuração da Pilha Alternativa ---
    stack_t ss = {};
    ss.ss_sp = alternate_stack; // Aponta para o nosso buffer de memória
    ss.ss_size = SIGSTKSZ;      // Define o tamanho
    ss.ss_flags = 0;

    // Informa ao sistema operacional sobre nossa pilha de emergência.
    if (sigaltstack(&ss, NULL) == -1) {
        perror("Erro ao configurar sigaltstack");
        exit(EXIT_FAILURE);
    }
    // -----------------------------------------

    // Usando sigaction para registrar o handler
    struct sigaction sa = {};
    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);
    // Esta é a flag crucial que diz: "Use a pilha alternativa se disponível"
    sa.sa_flags = SA_ONSTACK;

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("Erro ao configurar sigaction");
        exit(EXIT_FAILURE);
    }

    std::cout << "Iniciando a demonstração de Stack Overflow com pilha de emergência." << std::endl;
    causar_stackoverflow(1);
    
    return 0;
}