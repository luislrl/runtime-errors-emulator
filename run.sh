#!/bin/bash

# Este é o script que automatiza todo o processo.

# --- etapa 1: construir a imagem docker ---
# o script primeiro garante que a imagem 'emulator' está construída e atualizada.
echo "--> Etapa 1/2: Construindo/Verificando a imagem Docker 'emulator'..."
docker build -f Dockerfile.emulator -t error_emulator . > /dev/null

# verifica se a construção da imagem falhou
if [ $? -ne 0 ]; then
    echo "ERRO: A construção da imagem Docker falhou. Abortando."
    exit 1
fi

# --- etapa 2: executar o contêiner com todos os comandos necessários ---
# agora, ele inicia o contêiner e passa uma única "super-string" de comandos
# para serem executados lá dentro, em ordem.
echo "--> Etapa 2/2: Iniciando o contêiner e o emulador..."
docker run -it --rm --privileged error_emulator bash -c " \
    echo 'core' > /proc/sys/kernel/core_pattern && \
    ulimit -c unlimited && \
    ./emulator.sh \
"

echo "--> Emulador finalizado."