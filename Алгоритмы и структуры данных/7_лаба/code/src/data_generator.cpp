#include "data_generator.h"
#include <random>
#include <set>
#include <algorithm>

TestData generateTestData(int size) {
    TestData data;

    // Генерация уникальных случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, size * 10);

    std::set<int> uniqueNumbers;
    // Приводим size к size_t для корректного сравнения
    while (uniqueNumbers.size() < static_cast<size_t>(size)) {
        uniqueNumbers.insert(dis(gen));
    }

    // Заполняем все структуры одинаковыми данными
    data.arrayData.assign(uniqueNumbers.begin(), uniqueNumbers.end());
    data.listData.assign(uniqueNumbers.begin(), uniqueNumbers.end());

    // Для бинарного поиска нужна сортировка
    data.binaryData = data.arrayData;
    std::sort(data.binaryData.begin(), data.binaryData.end());

    // Разделяем на существующие и отсутствующие значения
    int halfSize = size / 2;
    data.existingValues.assign(
        data.arrayData.begin(),
        data.arrayData.begin() + halfSize
    );

    // Генерируем отсутствующие значения (за пределами диапазона)
    int maxVal = *std::max_element(data.arrayData.begin(), data.arrayData.end());
    for (int i = 0; i < halfSize; ++i) {
        data.missingValues.push_back(maxVal + i + 1);
    }

    return data;
}
