# Glossário Resumido de Erros em C++

Este arquivo explica de forma concisa os tipos de erros de programação do projeto.

---

### 1. Buffer Overflow (Estouro de Buffer)
Ocorre quando um programa escreve dados para além dos limites de um buffer, sobrescrevendo memória adjacente.
- **Consequência:** Corrupção de dados, falhas e vulnerabilidades de segurança.

---

### 2. Core Dumped
Não é um erro, mas o resultado de um. É um arquivo com um "snapshot" da memória do programa no momento em que ele travou, usado para depuração.

---

### 3. Deadlock (Bloqueio Mútuo)
Acontece quando dois ou mais processos/threads ficam travados, esperando um pelo outro por recursos que eles mesmos bloquearam.
- **Consequência:** O programa para de responder.

---

### 4. Memory Leak (Vazamento de Memória)
Ocorre quando memória alocada dinamicamente (`new`) não é liberada (`delete`), fazendo com que o consumo de memória do programa cresça sem parar.

---

### 5. Race Condition (Condição de Corrida)
Um bug de concorrência onde o resultado de uma operação depende da ordem imprevisível em que as threads são executadas, levando a resultados inconsistentes.

---

### 6. Segmentation Fault (Falha de Segmentação)
Erro causado pela tentativa de acessar uma área de memória proibida.
- **Causas Comuns:** Usar ponteiros nulos ou inválidos, ou acessar um array fora de seus limites.

---

### 7. Stack Overflow (Estouro de Pilha)
Acontece quando a pilha de chamadas (*call stack*) excede seu limite de memória.
- **Causa Comum:** Funções recursivas que rodam sem um caso de parada (recursão infinita).