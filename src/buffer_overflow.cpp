#include <iostream>
#include <cstring>
#include <csignal>
#include <cstdlib>

// manipulador de sinal personalizado para sigsegv (falha de segmentação)
void sigsegv_handler(int signum) {
    std::cout << "--- ERRO DETECTADO ---" << std::endl;
    std::cout << "Descrição: Falha de segmentação (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: Acesso indevido à memória, característico de um Buffer Overflow." << std::endl;
    std::cout << "O programa foi encerrado de forma controlada." << std::endl;
    std::cout << "----------------------" << std::endl;
    exit(signum); // encerra o programa
}

void vulneravel() {
    char buffer[10]; // cria um buffer pequeno com espaço para 10 bytes

    std::cout << "Tentando copiar uma string longa para um buffer pequeno...\n" << std::endl;
    // a função strcpy não verifica o tamanho do destino.
    /* copiamos uma string muito maior que a capacidade do buffer, 
    fazendo sobrescrever a memória adjacente na stack. */
    strcpy(buffer, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}

int main() {

    // registra o handler para o sinal de falha de segmentação
    signal(SIGSEGV, sigsegv_handler);

    std::cout << "Demonstração de Buffer Overflow.\n" << std::endl;
    vulneravel();

    // não vai chegar até aqui
    std::cout << "Demonstração concluída sem erros." << std::endl;
    return 0;
}