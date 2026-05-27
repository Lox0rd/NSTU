#include "DataStructure.h"
#include <iostream>
#include <fstream>

int main() {
    DataStructure<int> numbers;
    std::cout << "1. Создана пустая структура данных для целых чисел\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n\n";

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

    numbers.insert(1, 3);
    std::cout << "3. Вставлен элемент 3 на позицию с индексом 1\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после вставки: ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    numbers.sort();
    std::cout << "4. Выполнена сортировка элементов\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после сортировки: ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

    numbers.insertSorted(4);
    std::cout << "5. Добавлен элемент 4 с сохранением порядка (insertSorted)\n";
    std::cout << "   Текущий размер: " << numbers.getSize() << "\n";
    std::cout << "   Содержимое после insertSorted(4): ";
    for (size_t i = 0; i < numbers.getSize(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n\n";

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

    DataStructure<int> loadedNumbers;
    std::cout << "7. Создана новая пустая структура для загрузки данных\n";
    std::cout << "   Размер новой структуры: " << loadedNumbers.getSize() << "\n\n";

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
    return 0;
}
