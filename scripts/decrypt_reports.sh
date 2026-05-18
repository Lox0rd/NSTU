#!/bin/bash

# Проверка наличия пароля в аргументах
if [ $# -eq 0 ]; then
    echo "Использование: $0 <пароль>"
    echo "Пример: $0 mysecretpassword"
    exit 1
fi

PASSWORD="$1"

# Функция для поиска папок "Отчёты_locked" и дешифрования файлов
decrypt_reports() {
    local base_dir="$1"

    # Поиск всех папок с названием "Отчёты_locked"
    find "$base_dir" -type d -name "Отчёты_locked" | while read -r locked_dir; do
        # Определяем исходную папку "Отчёты" (убираем "_locked")
        local reports_dir="${locked_dir%_locked}"

        # Создаём папку "Отчёты", если её нет
        if [ ! -d "$reports_dir" ]; then
            echo "Папка $reports_dir не существует. Создаём..."
            mkdir -p "$reports_dir"
            if [ $? -ne 0 ]; then
                echo "Ошибка при создании папки: $reports_dir"
                continue
            else
                echo "Папка успешно создана: $reports_dir"
            fi
        fi

        echo "Обработка зашифрованной папки: $locked_dir"
        echo "Файлы будут восстановлены в: $reports_dir"

        # Рекурсивно ищем все зашифрованные файлы (.gpg)
        find "$locked_dir" -type f -name "*.gpg" | while read -r encrypted_file; do
            # Убираем расширение .gpg
            local original_path="${encrypted_file#$locked_dir/}"
            original_path="${original_path%.gpg}"
            # Полный путь для восстановленного файла
            local restored_file="$reports_dir/$original_path"

            # Создаём директорию для восстановленного файла, если нужно
            mkdir -p "$(dirname "$restored_file")"

            # Проверяем, существует ли файл, который мы хотим восстановить
            if [ -f "$restored_file" ]; then
                echo "Файл уже существует: $restored_file. Удаляем для замены."
                rm -f "$restored_file"
                if [ $? -ne 0 ]; then
                    echo "Ошибка при удалении существующего файла: $restored_file"
                    continue
                fi
            fi

            echo "Дешифрование: $encrypted_file -> $restored_file"
            # Дешифруем файл, передавая пароль через stdin
            echo "$PASSWORD" | gpg --batch -o "$restored_file" --passphrase-fd 0 "$encrypted_file"

            if [ $? -eq 0 ]; then
                echo "Успешно восстановлен: $restored_file"
            else
                echo "Ошибка при дешифровании: $encrypted_file"
                # Если дешифрование не удалось, удаляем потенциально повреждённый файл
                rm -f "$restored_file" 2>/dev/null
                exit 1
            fi
        done
    done
}

base_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
decrypt_reports "$base_dir"

echo "Процесс дешифрования завершён."
