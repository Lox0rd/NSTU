.PHONY: all install run coverage clean venv test

VENV_DIR = venv
REQUIREMENTS = requirements.txt
MAIN_SCRIPT = main.py

all: install run

install: venv
	@echo "Установка зависимостей..."
	$(VENV_DIR)/bin/pip install -r $(REQUIREMENTS)

venv:
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo "Создание виртуального окружения..."; \
		python -m venv $(VENV_DIR); \
	fi

# Запуск основного скрипта
run:
	@echo "Running $(MAIN_SCRIPT)..."
	$(VENV_DIR)/bin/python $(MAIN_SCRIPT)

test:
	@echo "Запуск тестов покрытия..."
	$(VENV_DIR)/bin/coverage run -m unittest

coverage: test
	@echo "Генерация отчёта..."
	$(VENV_DIR)/bin/coverage html

clean:
	@echo "Очистка..."
	rm -rf htmlcov/ .coverage coverage.xml
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -name "*.pyc" -delete 2>/dev/null || true

clean-venv:
	@echo "Удаление виртуального окружения..."
	rm -rf $(VENV_DIR)
