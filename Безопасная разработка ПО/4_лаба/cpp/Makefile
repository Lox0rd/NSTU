CXX = g++

FLAGS = -std=c++17 -O0 --coverage
LIBS = -lgtest -lgtest_main -pthread

SRC = main.cpp stack.cpp queue.cpp tree.cpp
TEST_SRC = test_runner.cpp stack.cpp queue.cpp tree.cpp

TARGET = tests
REPORT = coverage_report

all:
	$(CXX) $(FLAGS) $(SRC) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

coverage:
	rm -f *.gcda *.gcno coverage.info
	$(CXX) $(FLAGS) $(TEST_SRC) $(LIBS) -o $(TARGET)
	./$(TARGET)

	# Сбор данных покрытия
	lcov --capture --directory . \
	--output-file coverage.info \
	--ignore-errors inconsistent,unexecuted,empty

	# Фильтрация: исключаем системные библиотеки и тестовые файлы
	lcov --remove coverage.info '/usr/*' '*/test_runner.cpp' \
	--output-file coverage.info \
	--ignore-errors empty

	# Генерация HTML‑отчёта
	genhtml coverage.info --output-directory $(REPORT) \
	--ignore-errors empty


clean:
	rm -f $(TARGET) *.gcda *.gcno coverage.info
	rm -rf $(REPORT)
