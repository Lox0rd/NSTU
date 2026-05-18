#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <iostream>
#include <algorithm>

template<typename T>
class DataStructure {
private:
    T* data;          // Указатель на массив данных
    size_t size;      // Текущее количество элементов
    size_t capacity;  // Текущая ёмкость массива

    // Вспомогательная функция для увеличения ёмкости массива
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        size_t copy_size = (size < new_capacity) ? size : new_capacity;

        for (size_t i = 0; i < copy_size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор пустой структуры данных
    DataStructure() : data(nullptr), size(0), capacity(0) {}

    // Деструктор
    ~DataStructure() {
        delete[] data;
    }

    // Операция добавления элемента в конец
    void add(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Вставка элемента по логическому номеру (индекс)
    bool insert(size_t index, const T& value) {
        if (index > size) return false;

        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }

        // Сдвигаем элементы вправо
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        ++size;
        return true;
    }

    // Исключение элемента по логическому номеру
    bool remove(size_t index) {
        if (index >= size) return false;

        // Сдвигаем элементы влево
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size;
        return true;
    }

    // Сортировка (требуется наличие оператора < для типа T)
    void sort() {
        std::sort(data, data + size);
    }

    // Вставка с сохранением порядка (сортировка)
    void insertSorted(const T& value) {
    if (size >= capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    // Бинарный поиск позиции для вставки
    size_t pos = 0;
    while (pos < size && data[pos] < value) {
        ++pos;
    }

    // Сдвиг элементов вправо
    for (size_t i = size; i > pos; --i) {
        data[i] = data[i - 1];
    }

    data[pos] = value;
    ++size;
    }  


    // Получение размера структуры
    size_t getSize() const {
        return size;
    }

    // Доступ к элементу по индексу
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // Сохранение в текстовый поток
    friend std::ostream& operator<<(std::ostream& os, const DataStructure<T>& ds) {
        os << ds.size << "\n";  // Сначала сохраняем размер
        for (size_t i = 0; i < ds.size; ++i) {
            os << ds.data[i] << "\n";
        }
        return os;
    }

    // Загрузка из текстового потока
    friend std::istream& operator>>(std::istream& is, DataStructure<T>& ds) {
        size_t saved_size;
        is >> saved_size;

        // Очищаем существующую структуру
        ds.size = 0;
        if (saved_size > ds.capacity) {
            delete[] ds.data;
            ds.data = new T[saved_size];
            ds.capacity = saved_size;
        }

        // Загружаем элементы
        for (size_t i = 0; i < saved_size; ++i) {
            is >> ds.data[i];
            ++ds.size;
        }

        return is;
    }
};

#endif // DATASTRUCTURE_H
