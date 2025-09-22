#include <iostream>
#include <csignal>
#include <cstdlib>

// aloca memória para a pilha de emergência (tamanho recomendado pelo sistema).
static char* alternate_stack = new char[SIGSTKSZ];

// função que será executada quando o erro (SIGSEGV) for capturado.
void sigsegv_handler(int signum) {
    // imprime uma mensagem amigável explicando o erro.
    std::cout << "\n\n--- ERRO CRÍTICO DETECTADO (EM MODO DE SEGURANÇA) ---" << std::endl;
    std::cout << "Descrição: Falha de segmentação (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: STACK OVERFLOW (Estouro da Pilha de Chamadas)." << std::endl;
    std::cout << "O handler foi executado em uma pilha alternativa, pois a principal esgotou." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    
    // encerra o programa de forma controlada.
    exit(signum);
}

// função que chama a si mesma infinitamente para causar o stack overflow.
void causar_stackoverflow(long long contador) {
    // mostra o progresso da recursão na tela.
    std::cout << "\rProfundidade da recursão: " << contador << std::flush;
    // chama a si mesma novamente, aprofundando a recursão.
    causar_stackoverflow(contador + 1);
}

int main() {
    // --- 1. configuração da pilha alternativa ---
    stack_t ss = {};
    ss.ss_sp = alternate_stack; // Define o ponteiro da pilha.
    ss.ss_size = SIGSTKSZ;      // Define o tamanho da pilha.
    ss.ss_flags = 0;            // Flags (nenhuma neste caso).

    // registra a pilha de emergência no sistema operacional.
    if (sigaltstack(&ss, NULL) == -1) {
        perror("Erro ao configurar sigaltstack");
        exit(EXIT_FAILURE);
    }
    
    // --- 2. configuração do Signal Handler ---
    struct sigaction sa = {};
    sa.sa_handler = sigsegv_handler;   // define qual função irá tratar o sinal.
    sigemptyset(&sa.sa_mask);          // não bloqueia outros sinais.
    sa.sa_flags = SA_ONSTACK;          // importante: instrui o uso da pilha alternativa.

    // registra o handler para o sinal de falha de segmentação (SIGSEGV).
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("Erro ao configurar sigaction");
        exit(EXIT_FAILURE);
    }

    // --- 3. execução do código perigoso ---
    std::cout << "Iniciando a demonstração de Stack Overflow com pilha de emergência." << std::endl;
    // chama a função que vai causar o erro.
    causar_stackoverflow(1);
    
    return 0; // esta linha nunca será alcançada.
}