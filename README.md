# Runtime Error Emulator

Este projeto é um ambiente controlado para simular e estudar diferentes tipos de erros de programação em C++, como `Segmentation Fault`, `Stack Overflow`, `Deadlock`, entre outros. Ele utiliza Docker para criar um ambiente de execução isolado e consistente.

O emulador pode ser usado de duas formas principais:

1.  **Modo Script (Host):** Um script no seu computador que lança um contêiner descartável para cada erro.
2.  **Modo Interativo (Contêiner):** Um contêiner que, ao ser iniciado, apresenta um menu para você escolher qual erro simular internamente.

-----

## Requirements (Pré-requisitos)

  * [Docker](https://www.docker.com/products/docker-desktop/) instalado e em execução.
  * Um ambiente de terminal compatível com `bash`.
  * `git` para clonar o repositório.

-----

## Build (Construção das Imagens)

Antes de executar, você precisa construir a imagem Docker. Escolha o modo de operação que deseja usar.

### Modo 1: Script no Host (Recomendado)

Esta imagem contém apenas os programas compilados. O script `error_emulator.sh` no seu computador irá gerenciá-la.

```bash
docker build -t meus-programas-cpp .
```

*(Este comando usa o `Dockerfile` padrão)*

### Modo 2: Menu Interativo no Contêiner

Esta imagem contém os programas compilados e também o script de menu, que é definido como o ponto de entrada principal.

```bash
docker build -f Dockerfile.emulator -t emulador-interativo .
```

*(Note que usamos `-f Dockerfile.emulator` para especificar o arquivo de build)*

-----

## Run & Use (Execução e Uso)

### Modo 1: Usando o Script no Host

Este modo é ideal para executar erros específicos de forma rápida e isolada.

1.  **Execute o script:**

    ```bash
    docker run --rm -it error_emulator ./deadlock
    ```

### Modo 2: Usando o Menu Interativo no Contêiner

Este modo inicia um único contêiner que permanece ativo, permitindo que você execute vários testes dentro do mesmo ambiente.

1.  **Inicie o contêiner interativo:**
    ```bash
    docker run --rm error_emulator
    ```
    O menu aparecerá imediatamente, sendo executado de dentro do próprio contêiner. Para parar a simulação e o contêiner, escolha a opção `q` no menu.

-----

### Modo 3: Fluxo de Trabalho Automatizado (All-in-One)

Este modo é a forma mais simples e profissional de executar a demonstração completa de erros que exigem permissões especiais, como o `core_dumped`. Ele automatiza a construção e a execução do contêiner, além da configuração interna necessária, em um único comando.

#### O Script "run.sh"

[cite\_start]O script `run.sh` automatiza todo o processo[cite: 1]:

```bash
# este é o script que automatiza todo o processo.

# --- etapa 1: Construir a Imagem Docker ---
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
```

#### Como Usar este Modo

1.  [cite\_start]Dê permissão de execução ao script `run.sh`[cite: 1]: `chmod +x run.sh`
2.  [cite\_start]Execute o script para rodar o contêiner[cite: 1]: `./run.sh`

#### Verificação do Core Dump

[cite\_start]Para verificar a criação do arquivo `core` após a falha, siga estes passos em um segundo terminal (PowerShell, por exemplo)[cite: 1]:

  * Liste os contêineres em execução: `docker ps`
  * Pegue o ID do seu contêiner.
  * Entre no contêiner usando o ID obtido: `docker exec -it <ID_DO_CONTAINER> bash`
  * Dentro do contêiner, verifique a existência do arquivo `core`: `ls core`