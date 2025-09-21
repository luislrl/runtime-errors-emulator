#include <iostream>
#include <cstring>
#include <csignal>
#include <cstdlib>

void sigsegv_handler(int signum) {
    std::cout << "\n--- ERRO DETECTADO ---" << std::endl;
    std::cout << "Descrição: Falha de segmentação (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: Acesso indevido à memória, característico de um Buffer Overflow." << std::endl;
    std::cout << "O programa foi encerrado de forma controlada." << std::endl;
    std::cout << "----------------------" << std::endl;
    exit(signum);
}

void vulneravel() {
    char buffer[10];
    std::cout << "Tentando copiar uma string longa para um buffer pequeno..." << std::endl;
    strcpy(buffer, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}

int main() {
    signal(SIGSEGV, sigsegv_handler);

    std::cout << "Iniciando a demonstração de Buffer Overflow." << std::endl;
    vulneravel();
    
    std::cout << "Demonstração concluída sem erros." << std::endl; 
    return 0;
}