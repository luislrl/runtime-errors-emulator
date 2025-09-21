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

# Compilação de cada .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Rodar
run: all
	./$(EXEC)
