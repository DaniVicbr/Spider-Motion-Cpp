# Variáveis de compilação
CXX = clang++
CXXFLAGS = -std=c++17 -Wall

# Caminhos padrão do Homebrew (onde a Raylib foi instalada)
INCLUDE_PATHS = -I/opt/homebrew/include
LIBRARY_PATHS = -L/opt/homebrew/lib

# Frameworks exigidos pelo macOS para rodar a interface gráfica e áudio da Raylib
FRAMEWORKS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Nome do executável final
TARGET = jogo

all:
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -lraylib $(FRAMEWORKS)
	./$(TARGET)

