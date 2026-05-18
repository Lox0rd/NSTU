#!/bin/bash

# Проверка наличия пароля в аргументах
if [ $# -eq 0 ]; then
    echo "Использование: $0 <пароль>"
    echo "Пример: $0 mysecretpassword"
    exit 1
fi

PASSWORD="$1"

# Функция для рекурсивного поиска папок "Отчёты" и шифрования файлов
encrypt_reports() {
    local base_dir="$1"

    # Поиск всех папок с названием "Отчёты"
    find "$base_dir" -type d -name "Отчёты" | while read -r reports_dir; do
        # Путь к папке для зашифрованных файлов
        local locked_dir="${reports_dir}_locked"

        # Создаём папку для зашифрованных файлов, если её нет
        mkdir -p "$locked_dir"

        echo "Обработка папки: $reports_dir"
        echo "Зашифрованные файлы будут сохранены в: $locked_dir"

        # Рекурсивно ищем все файлы в папке "Отчёты" (исключая саму папку _locked)
        find "$reports_dir" -type f ! -path "$locked_dir/*" | while read -r file; do
            # Получаем относительный путь файла внутри папки "Отчёты"
            local rel_path="${file#$reports_dir/}"
            # Путь для зашифрованного файла
            local encrypted_file="$locked_dir/${rel_path}.gpg"

            # Создаём директорию для зашифрованного файла, если нужно
            mkdir -p "$(dirname "$encrypted_file")"

            echo "Шифрование: $file"
            # Шифруем файл с помощью gpg, передавая пароль через stdin
            echo "$PASSWORD" | gpg --batch --symmetric --cipher-algo AES256 \
                --no-compress --passphrase-fd 0 -o "$encrypted_file" "$file"

            if [ $? -eq 0 ]; then
                echo "Успешно зашифрован: $encrypted_file"
            else
                echo "Ошибка при шифровании: $file"
                exit 1
            fi
        done
    done
}

base_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
encrypt_reports "$base_dir"

echo "Процесс шифрования завершён."

