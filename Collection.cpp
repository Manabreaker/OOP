#include "Collection.h"
#include <stdexcept>
#include <iostream>
#include <utility>

// Конструктор по умолчанию
template<typename T>
Collection<T>::Collection() : table(nullptr), capacity(8), count(0), load_factor(0.75f) {
    table = new Bucket[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = false;
        table[i].deleted = false;
    }
}

// Конструктор копирования
template<typename T>
Collection<T>::Collection(const Collection<T>& other) : table(nullptr), capacity(other.capacity), count(other.count), load_factor(other.load_factor) {
    table = new Bucket[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = other.table[i].occupied;
        table[i].deleted = other.table[i].deleted;
        if (other.table[i].occupied && !other.table[i].deleted) {
            table[i].value = other.table[i].value;
        }
    }
}

// Оператор присваивания
template<typename T>
Collection<T>& Collection<T>::operator=(const Collection<T>& other) {
    if (this == &other) return *this;

    clear();
    delete[] table;

    capacity = other.capacity;
    count = other.count;
    load_factor = other.load_factor;

    table = new Bucket[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = other.table[i].occupied;
        table[i].deleted = other.table[i].deleted;
        if (other.table[i].occupied && !other.table[i].deleted) {
            table[i].value = other.table[i].value;
        }
    }
    return *this;
}

// Деструктор
template<typename T>
Collection<T>::~Collection() {
    clear();
    delete[] table;
}

// Очистка коллекции
template<typename T>
void Collection<T>::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = false;
        table[i].deleted = false;
    }
    count = 0;
}

// Размер коллекции
template<typename T>
size_t Collection<T>::size() const {
    return count;
}

// Увеличение ёмкости и перезаполнение
template<typename T>
void Collection<T>::rehash() {
    size_t newCapacity = capacity * 2;
    auto* newTable = new Bucket[newCapacity];
    for (size_t i = 0; i < newCapacity; ++i) {
        newTable[i].occupied = false;
        newTable[i].deleted = false;
    }

    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].occupied && !table[i].deleted) {
            size_t h = hash_func(table[i].value) % newCapacity;
            while (newTable[h].occupied && !newTable[h].deleted) {
                h = (h + 1) % newCapacity;
            }
            newTable[h].occupied = true;
            newTable[h].deleted = false;
            newTable[h].value = table[i].value;
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

// Увеличение размера при необходимости
template<typename T>
void Collection<T>::ensureCapacity() {
    if ((float)count / (float)capacity > load_factor) {
        rehash();
    }
}

// Поиск индекса элемента в таблице
template<typename T>
size_t Collection<T>::findIndex(const T& value, bool exactFind) const {
    size_t h = hash_func(value) % capacity;
    size_t start = h;
    bool firstDeletedFound = false;
    size_t deletedIndex = capacity;

    while (true) {
        if (!table[h].occupied) {
            return (firstDeletedFound ? deletedIndex : h);
        } else if (table[h].occupied && !table[h].deleted) {
            if (table[h].value == value) {
                return h;
            }
        } else if (table[h].occupied && table[h].deleted) {
            if (!firstDeletedFound) {
                firstDeletedFound = true;
                deletedIndex = h;
            }
        }

        h = (h + 1) % capacity;
        if (h == start) {
            return (firstDeletedFound ? deletedIndex : capacity);
        }
    }
}

// Добавление элемента
template<typename T>
void Collection<T>::add(const T& value) {
    if (contains(value)) {
        return;
    }

    ensureCapacity();
    size_t idx = findIndex(value, false);
    table[idx].value = value;
    table[idx].occupied = true;
    table[idx].deleted = false;
    count++;
}

// Удаление элемента
template<typename T>
void Collection<T>::remove(const T& value) {
    size_t idx = findIndex(value, true);
    if (idx < capacity && table[idx].occupied && !table[idx].deleted) {
        table[idx].deleted = true;
        count--;
    }
}

// Проверка наличия элемента
template<typename T>
bool Collection<T>::contains(const T& value) const {
    size_t idx = findIndex(value, true);
    return (idx < capacity && table[idx].occupied && !table[idx].deleted && table[idx].value == value);
}

// Оператор доступа по ключу
template<typename T>
T& Collection<T>::operator[](const T& key) {
    ensureCapacity();
    size_t idx = findIndex(key, false);
    if (!table[idx].occupied || table[idx].deleted) {
        table[idx].value = key;
        table[idx].occupied = true;
        table[idx].deleted = false;
        count++;
    }
    return table[idx].value;
}

// Обновление элемента
template<typename T>
void Collection<T>::update(const T& oldKey, const T& newKey) {
    remove(oldKey);
    add(newKey);
}

// Оператор пересечения коллекций
template<typename T>
Collection<T> Collection<T>::operator&&(const Collection<T>& other) const {
    Collection<T> result;
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].occupied && !table[i].deleted && other.contains(table[i].value)) {
            result.add(table[i].value);
        }
    }
    return result;
}

// Оператор равенства
template<typename T>
bool Collection<T>::operator==(const Collection<T>& other) const {
    if (size() != other.size()) return false;
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].occupied && !table[i].deleted) {
            if (!other.contains(table[i].value)) {
                return false;
            }
        }
    }
    return true;
}

// Оператор добавления элемента
template<typename T>
Collection<T>& Collection<T>::operator<<(const T& value) {
    add(value);
    return *this;
}

// Сохранение в файл
template<typename T>
void Collection<T>::saveToFile(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open file for writing");
    }

    size_t sz = size();
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));

    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].occupied && !table[i].deleted) {
            saveElement(out, table[i].value);
        }
    }
}

// Загрузка из файла
template<typename T>
void Collection<T>::loadFromFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open file for reading");
    }

    clear();

    size_t sz;
    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));

    for (size_t i = 0; i < sz; ++i) {
        T val;
        loadElement(in, val);
        add(val);
    }
}

// Сериализация тривиальных типов
template<typename T>
template<typename U>
typename std::enable_if<std::is_arithmetic<U>::value>::type
Collection<T>::saveElement(std::ofstream& out, const U& val) const {
    out.write(reinterpret_cast<const char*>(&val), sizeof(U));
}

template<typename T>
template<typename U>
typename std::enable_if<std::is_arithmetic<U>::value>::type
Collection<T>::loadElement(std::ifstream& in, U& val) {
    in.read(reinterpret_cast<char*>(&val), sizeof(U));
}

// Сериализация строк
template<typename T>
template<typename U>
typename std::enable_if<!std::is_arithmetic<U>::value && std::is_same<U, std::string>::value>::type
Collection<T>::saveElement(std::ofstream& out, const std::string& val) const {
    size_t len = val.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(val.data(), len);
}

template<typename T>
template<typename U>
typename std::enable_if<!std::is_arithmetic<U>::value  && std::is_same<U, std::string>::value>::type
Collection<T>::loadElement(std::ifstream& in, std::string& val) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    val.resize(len);
    in.read(&val[0], len);
}
