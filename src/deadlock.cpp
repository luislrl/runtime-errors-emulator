#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <csignal>
#include <cstdlib>

// dois mutex globais que serão disputados pelas threads.
std::mutex mutex1;
std::mutex mutex2;

// manipulador para o sinal de interrupção (ctrl+c)
void sigint_handler(int signum) {
    std::cout << "\n --- PROGRAMA INTERROMPIDO ---" << std::endl;
    std::cout << "Descrição: Sinal de interrupção recebido (Signal " << signum << ")." << std::endl;
    std::cout << "Causa Provável: O programa estava em um estado de Deadlock e não pôde continuar." << std::endl;
    std::cout << "Encerrando..." << std::endl;
    std::cout << "---------------------------" << std::endl;
    exit(signum);
}

void thread_func1() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::cout << "[Thread 1] Travou o mutex 1. Tentando travar o mutex 2..." << std::endl;

    // pausa para garantir que a thread 2 tenha tempo de travar o mutex2
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::lock_guard<std::mutex> lock2(mutex2); // a thread 1 vai ficar presa aqui, esperando a thread 2 liberar o mutex2
}

void thread_func2() {
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "[Thread 2] Travou o mutex 2. Tentando travar o mutex 1..." << std::endl;

    // pausa para garantir que a thread 1 tenha tempo de travar o mutex1
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::lock_guard<std::mutex> lock1(mutex1); // a thread 2 vai ficar presa aqui, esperando a thread 1 liberar o mutex1
}

int main() {
    // registra o handler para o sinal sigint (ctrl+c)
    signal(SIGINT, sigint_handler);

    std::cout << "Demonstração de Deadlock.\n" << std::endl;
    std::cout << "O programa irá travar. Pressione Ctrl+C para encerrar com uma mensagem.\n" << std::endl;

    // cria e inicia as duas threads
    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    /* o programa principal espera as threads terminarem.
    como elas nunca terminam, o programa fica preso aqui. */
    t1.join();
    t2.join();

    // não vai chegar até aqui
    std::cout << "Demonstração concluída." << std::endl;
    return 0;
}