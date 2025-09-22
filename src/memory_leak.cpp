#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <new>

// Função para imprimir a mensagem de erro e sair.
void handle_out_of_memory(long long leaked_mb) {
    std::cout << "\n\n--- ERRO CRÍTICO TRATADO ---" << std::endl;
    std::cout << "Descrição: Falha ao alocar memória." << std::endl;
    std::cout << "Causa Provável: MEMORY LEAK (Vazamento de Memória)." << std::endl;
    std::cout << "O programa consumiu toda a RAM disponível." << std::endl;
    std::cout << "Memória total vazada: " << leaked_mb << " MB." << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    exit(1);
}

int main() {
    std::vector<char*> leaked_memory_pointers;
    long long megabytes_leaked = 0;
    const int CHUNK_SIZE_MB = 10;
    const size_t chunk_size_bytes = CHUNK_SIZE_MB * 1024 * 1024;

    std::cout << "Iniciando a demonstração de Memory Leak..." << std::endl;

    try {
        while (true) {
            // Usamos (std::nothrow) para que new retorne nullptr em vez de lançar exceção.
            // Isso nos dá controle manual.
            char* chunk = new(std::nothrow) char[chunk_size_bytes];

            if (chunk == nullptr) {
                // Se a alocação falhou, chamamos nosso handler e saímos.
                handle_out_of_memory(megabytes_leaked);
            }
            
            leaked_memory_pointers.push_back(chunk);
            megabytes_leaked += CHUNK_SIZE_MB;

            if (megabytes_leaked % 100 == 0) {
                std::cout << "\rMemória vazada até agora: " << megabytes_leaked << " MB..." << std::flush;
            }
        }
    } catch (const std::bad_alloc& e) {
        // O catch ainda está aqui como uma segunda rede de segurança.
        handle_out_of_memory(megabytes_leaked);
    }

    return 0;
}