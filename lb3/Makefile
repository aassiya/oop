# Переменные
CXX = g++
CXXFLAGS = -Wall -g -Iinclude
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cpp)  # Список всех .cpp файлов
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC)) # Объектные файлы
TARGET = main

# Основное правило
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

# Компиляция .cpp в .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)  # Создание build для Windows
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка временных файлов
clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET) 2>nul
