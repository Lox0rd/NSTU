#include "DataStructure.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ СТРУКТУРЫ ДАННЫХ ===\n\n";

    // 1. СОЗДАНИЕ СТРУКТУРЫ ДАННЫХ
    // Создаём экземпляр шаблона класса DataStructure для типа int
    // В памяти выделяется минимальная структура с нулевыми параметрами:
    // data = nullptr, size = 0, capacity = 0
    DataStructure<int> numbers;
    std::cout << "1. Создана пустая структура данных для целых чисел\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n\n";

    // 2. ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ В КОНЕЦ
    // Метод add() добавляет элементы в конец массива
    // При первом добавлении автоматически выделяется память (capacity = 1)
    // При последующих добавлениях, когда size >= capacity, происходит resize()
    numbers.add(5);
    numbers.add(2);
    numbers.add(8);
    std::cout << "2. Добавлены элементы 5, 2, 8 в конец структуры\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое: ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    // 3. ВСТАВКА ЭЛЕМЕНТА ПО ИНДЕКСУ
    // Метод insert(1, 3) вставляет число 3 на позицию с индексом 1
    // Исходный массив: [5, 2, 8]
    // После вставки: [5, 3, 2, 8] — элемент 2 сдвигается на позицию 2
    numbers.insert(1, 3);
    std::cout << "3. Вставлен элемент 3 на позицию с индексом 1\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после вставки: ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    // 4. СОРТИРОВКА ЭЛЕМЕНТОВ
    // Метод sort() сортирует массив по возрастанию
    // Использует std::sort, который требует наличия operator< для типа T
    // Исходный массив: [5, 3, 2, 8]
    // После сортировки: [2, 3, 5, 8]
    numbers.sort();
    std::cout << "4. Выполнена сортировка элементов\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после сортировки: ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    // 5. ИСПОЛЬЗОВАНИЕ insertSorted()
    // Метод insertSorted() сначала добавляет элемент в конец, затем сортирует весь массив
    // Это менее эффективно, чем бинарный поиск с вставкой, но просто в реализации
    numbers.insertSorted(4);
    std::cout << "5. Добавлен элемент 4 с сохранением порядка (insertSorted)\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после insertSorted(4): ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    // 6. СОХРАНЕНИЕ В ФАЙЛ
    // Оператор << сохраняет структуру в текстовый файл:
    // - сначала записывается размер массива (число 5 на отдельной строке);
    // - затем последовательно все элементы, каждый на новой строке.
    std::ofstream outFile("data.txt");
    if (outFile.is_open()) {
        outFile << numbers;
        outFile.close();
        std::cout << "6. Структура сохранена в файл 'data.txt'\n";
        std::cout << "   Содержимое файла будет выглядеть так:\n";
        std::cout << "   5\n   2\n   3\n   4\n   5\n   8\n\n";
    } else {
        std::cerr << "Ошибка: не удалось открыть файл для записи!\n";
        return 1;
    }

    // 7. ЗАГРУЗКА ИЗ ФАЙЛА
    // Создаём новую пустую структуру для демонстрации загрузки
    DataStructure<int> loadedNumbers;
    std::cout << "7. Создана новая пустая структура для загрузки данных\n";
    std::cout << "   Размер новой структуры: " << loadedNumbers.getSize() << "\n\n";

    // Оператор >> загружает данные из файла:
    // - читает размер (5);
    // - выделяет необходимую память;
    // - последовательно читает 5 элементов и заполняет массив.
    std::ifstream inFile("data.txt");
    if (inFile.is_open()) {
        inFile >> loadedNumbers;
        inFile.close();
        std::cout << "8. Данные загружены из файла 'data.txt' в новую структуру\n";
        std::cout << "   Размер загруженной структуры: " << loadedNumbers.getSize() << "\n";
        std::cout << "   Содержимое загруженной структуры: ";
        for (size_t i = 0; i < loadedNumbers.getSize(); ++i) {
            std::cout << loadedNumbers[i] << " ";
        }
        std::cout << "\n\n";
    } else {
        std::cerr << "Ошибка: не удалось открыть файл для чтения!\n";
        return 1;
    }

    // 8. ПРОВЕРКА КОРРЕКТНОСТИ ЗАГРУЗКИ
    // Сравниваем исходный и загруженный массивы
    bool isEqual = (numbers.getSize() == loadedNumbers.getSize());
    if (isEqual) {
        for (size_t i = 0; i < numbers.getSize(); ++i) {
            if (numbers[i] != loadedNumbers[i]) {
                isEqual = false;
                break;
            }
        }
    }

    std::cout << "9. ПРОВЕРКА КОРРЕКТНОСТИ ЗАГРУЗКИ:\n";
    if (isEqual) {
        std::cout << "   Успешно! Исходная и загруженная структуры идентичны.\n";
    } else {
        std::cout << "   Ошибка! Данные не совпадают.\n";
    }

    std::cout << "\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n";

    return 0;
}
