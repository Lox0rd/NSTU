# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Целевой файл
TARGET = search_app

# Директории с исходными и заголовочными файлами
SRC_DIR = src
INCLUDE_DIR = include

# Исходные файлы
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/array_search.cpp \
       $(SRC_DIR)/list_search.cpp \
       $(SRC_DIR)/binary_search.cpp \
       $(SRC_DIR)/avl_tree.cpp \
       $(SRC_DIR)/hash_table.cpp \
       $(SRC_DIR)/data_generator.cpp

# Объектные файлы (автоматически генерируются из исходных)
OBJS = $(SRCS:.cpp=.o)

# Правило для сборки основной цели — исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Правило компиляции: преобразует каждый .cpp‑файл в .o‑файл
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило очистки: удаляет все объектные файлы и исполняемый файл
clean:
	rm -f $(OBJS) $(TARGET)

# Правило полной пересборки: сначала очищает проект, затем собирает заново
rebuild: clean $(TARGET)

# Правило установки зависимостей (опционально)
depend:
	makedepend $(SRCS)

.PHONY: clean rebuild depend
