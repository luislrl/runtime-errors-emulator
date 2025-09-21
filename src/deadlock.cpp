#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <csignal>
#include <cstdlib>

std::mutex mutex1;
std::mutex mutex2;

void sigint_handler(int signum) {
    std::cout << "\n\n--- PROGRAMA INTERROMPIDO ---" << std::endl;
    std::cout << "Descrição: Sinal de interrupção recebido (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: O programa estava em um estado de Deadlock e não pôde continuar." << std::endl;
    std::cout << "Encerrando..." << std::endl;
    std::cout << "---------------------------" << std::endl;
    exit(signum);
}

void thread_func1() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::cout << "[Thread 1] Travou o mutex 1. Tentando travar o mutex 2..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(mutex2);
}

void thread_func2() {
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "[Thread 2] Travou o mutex 2. Tentando travar o mutex 1..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock1(mutex1);
}

int main() {

    signal(SIGINT, sigint_handler);

    std::cout << "Iniciando a demonstração de Deadlock." << std::endl;
    std::cout << "O programa irá travar. Pressione Ctrl+C para encerrar com uma mensagem." << std::endl;

    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    t1.join();
    t2.join();

    std::cout << "Demonstração concluída." << std::endl;
    return 0;
}