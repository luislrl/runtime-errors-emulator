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
    docker run --rm error_emulator ./deadlock
    ```

### Modo 2: Usando o Menu Interativo no Contêiner

Este modo inicia um único contêiner que permanece ativo, permitindo que você execute vários testes dentro do mesmo ambiente.

1.  **Inicie o contêiner interativo:**
    ```bash
    docker run --rm error_emulator
    ```
    O menu aparecerá imediatamente, sendo executado de dentro do próprio contêiner. Para parar a simulação e o contêiner, escolha a opção `q` no menu.

-----