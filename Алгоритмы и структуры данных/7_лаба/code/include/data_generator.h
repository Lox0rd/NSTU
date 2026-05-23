#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <list>
#include <unordered_map>
#include <string>

struct TestData {
    std::vector<int> arrayData;
    std::list<int> listData;
    std::vector<int> binaryData; // отсортированные данные
    std::vector<int> existingValues; // существующие значения для поиска
    std::vector<int> missingValues; // отсутствующие значения для поиска
};

TestData generateTestData(int size);

#endif
