#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <chrono>
#include "array_search.h"
#include "list_search.h"
#include "binary_search.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "data_generator.h"

using namespace std;
using namespace std::chrono;

// Функция для измерения времени выполнения функции
template<typename Func>
double measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

int main() {
    const int DATA_SIZE = 5000;

    cout << "Генерация тестовых данных (" << DATA_SIZE << " элементов)..." << endl;
    TestData testData = generateTestData(DATA_SIZE);

    // Файл для сохранения результатов
    ofstream resultsFile("performance_results.csv");
    resultsFile << "Algorithm,SearchType,AverageTimeMs\n";

    cout << "Данные сгенерированы. Начинаем тестирование алгоритмов." << endl;
    cout << "==========================================================" << endl;

    // 2.1 Поиск в неупорядоченном массиве
    cout << "2.1 Поиск в массиве:" << endl;
    double arrayExistingTime = 0.0, arrayMissingTime = 0.0;

    for (int val : testData.existingValues) {
        arrayExistingTime += measureTime([&]() {
            linearSearch(testData.arrayData.data(), testData.arrayData.size(), val);
        });
    }
    arrayExistingTime /= testData.existingValues.size();

    for (int val : testData.missingValues) {
        arrayMissingTime += measureTime([&]() {
            linearSearch(testData.arrayData.data(), testData.arrayData.size(), val);
        });
    }
    arrayMissingTime /= testData.missingValues.size();

    cout << "  Среднее время успешного поиска: " << arrayExistingTime << " мс" << endl;
    cout << "  Среднее время безуспешного поиска: " << arrayMissingTime << " мс" << endl;
    resultsFile << "Array,Existing," << arrayExistingTime << "\n";
    resultsFile << "Array,Missing," << arrayMissingTime << "\n";

    // 2.2 Поиск в неупорядоченном списке
    cout << "\n2.2 Поиск в списке:" << endl;
    double listExistingTime = 0.0, listMissingTime = 0.0;

    for (int val : testData.existingValues) {
        listExistingTime += measureTime([&]() {
            listSearch(testData.listData, val);
        });
    }
    listExistingTime /= testData.existingValues.size();

    for (int val : testData.missingValues) {
        listMissingTime += measureTime([&]() {
            listSearch(testData.listData, val);
        });
    }
    listMissingTime /= testData.missingValues.size();

    cout << "  Среднее время успешного поиска: " << listExistingTime << " мс" << endl;
    cout << "  Среднее время безуспешного поиска: " << listMissingTime << " мс" << endl;
    resultsFile << "List,Existing," << listExistingTime << "\n";
    resultsFile << "List,Missing," << listMissingTime << "\n";

    // 2.3 Бинарный поиск в упорядоченном массиве
    cout << "\n2.3 Бинарный поиск:" << endl;
    double binaryExistingTime = 0.0, binaryMissingTime = 0.0;

    for (int val : testData.existingValues) {
        binaryExistingTime += measureTime([&]() {
            binarySearch(testData.binaryData.data(), testData.binaryData.size(), val);
        });
    }
    binaryExistingTime /= testData.existingValues.size();

    for (int val : testData.missingValues) {
        binaryMissingTime += measureTime([&]() {
            binarySearch(testData.binaryData.data(), testData.binaryData.size(), val);
        });
    }
    binaryMissingTime /= testData.missingValues.size();

    cout << "  Среднее время успешного поиска: " << binaryExistingTime << " мс" << endl;
    cout << "  Среднее время безуспешного поиска: " << binaryMissingTime << " мс" << endl;
    resultsFile << "Binary,Existing," << binaryExistingTime << "\n";
    resultsFile << "Binary,Missing," << binaryMissingTime << "\n";

    // 2.4 Поиск в АВЛ‑дереве
    cout << "\n2.4 Поиск в АВЛ-дереве:" << endl;
    AVLTree tree;

    // Заполняем АВЛ‑дерево данными
    for (int val : testData.arrayData) {
        tree.insert(val);
    }

    double avlExistingTime = 0.0, avlMissingTime = 0.0;

    for (int val : testData.existingValues) {
        avlExistingTime += measureTime([&]() {
            tree.search(val);
        });
    }
    avlExistingTime /= testData.existingValues.size();

    for (int val : testData.missingValues) {
        avlMissingTime += measureTime([&]() {
            tree.search(val);
        });
    }
    avlMissingTime /= testData.missingValues.size();

    cout << "  Среднее время успешного поиска: " << avlExistingTime << " мс" << endl;
    cout << "  Среднее время безуспешного поиска: " << avlMissingTime << " мс" << endl;
    resultsFile << "AVLTree,Existing," << avlExistingTime << "\n";
    resultsFile << "AVLTree,Missing," << avlMissingTime << "\n";

    // 2.5 Поиск в хеш‑таблице
    cout << "\n2.5 Поиск в хеш-таблице:" << endl;
    HashTable hashTable;

    // Заполняем хеш‑таблицу данными
    int counter = 1;
    for (int val : testData.arrayData) {
        hashTable.insert(val, "value_" + to_string(counter++));
    }

    double hashExistingTime = 0.0, hashMissingTime = 0.0;
    string resultStr;

    for (int val : testData.existingValues) {
        hashExistingTime += measureTime([&]() {
            hashTable.search(val, resultStr);
        });
    }
    hashExistingTime /= testData.existingValues.size();

    for (int val : testData.missingValues) {
        hashMissingTime += measureTime([&]() {
            hashTable.search(val, resultStr);
        });
    }
    hashMissingTime /= testData.missingValues.size();

    cout << "  Среднее время успешного поиска: " << hashExistingTime << " мс" << endl;
    cout << "  Среднее время безуспешного поиска: " << hashMissingTime << " мс" << endl;
    resultsFile << "HashTable,Existing," << hashExistingTime << "\n";
    resultsFile << "HashTable,Missing," << hashMissingTime << "\n";

    resultsFile.close();

    cout << "\nВсе тесты завершены с использованием одинаковых входных данных." << endl;
    cout << "Результаты сохранены в файл performance_results.csv" << endl;

    return 0;
}