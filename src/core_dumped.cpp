#include <iostream>
#include <csignal>
#include <cstdlib>

/* handler para sigsegv, apenas para notificar que o erro ocorreu.
após este handler, o sistema operacional irá encerrar o programa
e, gerar o core dump.*/
void sigsegv_handler(int signum) {
    std::cout << "--- ERRO FATAL DETECTADO ---" << std::endl;
    std::cout << "Descrição: Falha de segmentação (Signal " << signum << ")." << std::endl;
    std::cout << "Causa: Tentativa de escrita em um endereço de memória inválido (ponteiro nulo)." << std::endl;
    std::cout << "O sistema operacional irá agora encerrar o programa." << std::endl;
    std::cout << "Se 'ulimit -c' estiver configurado, um arquivo 'core' será gerado." << std::endl;
    std::cout << "--------------------------" << std::endl;
    
    // devolve o handler para o padrão para que o core dump seja gerado.
    signal(signum, SIG_DFL);
    raise(signum);
}

int main() {
    // registra o handler personalizado para dar uma mensagem.
    signal(SIGSEGV, sigsegv_handler);

    std::cout << "Demonstração de Core Dump.\n" << std::endl;
    std::cout << "Provocando um erro de acesso à memória para gerar um core dump...\n" << std::endl;

    // cria um ponteiro que não aponta para lugar nenhum (nulo).
    int *ponteiro_invalido = nullptr;

    /* tenta escrever no endereço de memória inválido (endereço 0). 
    esta é a linha que causará a falha de segmentação (SIGSEGV). */
    *ponteiro_invalido = 123;

    // não vai chegar até aqui
    std::cout << "Demonstração concluída." << std::endl;

    return 0;
}