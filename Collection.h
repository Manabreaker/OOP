#ifndef COLLECTION_H
#define COLLECTION_H

#include <functional>
#include <string>
#include <fstream>
#include <stdexcept>

template<typename T>
class Collection {
private:
    struct Bucket {
        bool occupied{};
        bool deleted{};
        T value{};
    };

    Bucket* table;
    size_t capacity;
    size_t count;
    float load_factor;

    std::hash<T> hash_func;

    void rehash();
    void ensureCapacity();
    [[nodiscard]] size_t findIndex(const T& value, bool exactFind = true) const;

public:
    Collection();
    Collection(const Collection<T>& other);
    Collection<T>& operator=(const Collection<T>& other);
    ~Collection();

    void clear();
    [[nodiscard]] size_t size() const;

    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);

    void add(const T& value);
    void remove(const T& value);
    [[nodiscard]] bool contains(const T& value) const;
    T& operator[](const T& key);
    void update(const T& oldKey, const T& newKey);

    Collection<T> operator&&(const Collection<T>& other) const;
    bool operator==(const Collection<T>& other) const;
    Collection<T>& operator<<(const T& value);

private:
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    saveElement(std::ofstream& out, const U& val) const;

    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    loadElement(std::ifstream& in, U& val);

    template<typename U = T>
    typename std::enable_if<!std::is_arithmetic<U>::value && std::is_same<U, std::string>::value>::type
    saveElement(std::ofstream& out, const std::string& val) const;

    template<typename U = T>
    typename std::enable_if<!std::is_arithmetic<U>::value && std::is_same<U, std::string>::value>::type
    loadElement(std::ifstream& in, std::string& val);
};

#include "Collection.cpp" // Для шаблонной реализации

#endif // COLLECTION_H
