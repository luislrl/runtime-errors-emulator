#include <iostream>
#include <thread>
#include <vector>

long long shared_counter = 0;

void increment_counter() {
    for (int i = 0; i < 1000000; ++i) {
        shared_counter++;
    }
}

int main() {
    std::cout << "Iniciando demonstração de condição de corrida..." << std::flush;

    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "\nValor final esperado (sem condição de corrida): 2000000" << std::endl;
    std::cout << "Valor final real (com condição de corrida):   " << shared_counter << std::endl;

    if (shared_counter != 2000000) {
        std::cout << "\nO resultado é diferente do esperado! A condição de corrida ocorreu." << std::endl;
    } else {
        std::cout << "\nIncrivelmente, o resultado foi o esperado. Tente rodar novamente." << std::endl;
    }

    return 0;
}