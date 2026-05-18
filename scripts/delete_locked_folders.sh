#!/bin/bash

# Функция для поиска и удаления папок "Отчёты_locked"
delete_locked_folders() {
    local base_dir="$1"
    local found_count=0
    local deleted_count=0

    echo "Поиск папок 'Отчёты_locked' в директории: $base_dir"
    echo "---"

    # Поиск всех папок с названием "Отчёты_locked"
    find "$base_dir" -type d -name "Отчёты_locked" | while read -r locked_dir; do
        if [ -d "$locked_dir" ]; then
            found_count=$((found_count + 1))
            echo "Найдена папка: $locked_dir"

            # Пытаемся удалить папку
            if rm -rf "$locked_dir"; then
                deleted_count=$((deleted_count + 1))
                echo "  ✓ Удалена успешно"
            else
                echo "  ✗ Ошибка при удалении"
            fi
        fi
    done

    # Если ничего не найдено
    if [ $found_count -eq 0 ]; then
        echo "Папки 'Отчёты_locked' не найдены в директории: $base_dir"
    else
        echo "---"
        echo "Найдено папок: $found_count"
        echo "Удалено папок: $deleted_count"
    fi
}

base_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
delete_locked_folders "$base_dir"

echo "Процесс удаления завершён."