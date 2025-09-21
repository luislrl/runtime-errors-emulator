# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Nome do executável
EXEC = linkedlist

# Regra principal
all: $(EXEC)

# Linkagem do executável
$(EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Adiciona o diretório de objetos como uma dependência de ordem (order-only).
# Isso garante que o diretório seja criado antes de qualquer compilação.
$(OBJ_FILES): | $(OBJ_DIR)

# Compilação de cada .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar o diretório de objetos, se ele não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Rodar
run: all
	./$(EXEC)