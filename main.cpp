#include <iostream>
#include <cassert>
#include "Collection.h"

int main() {
    // 1. Коллекция, созданная конструктором по умолчанию, имеет размер 0.
    Collection<int> c1;
    assert(c1.size() == 0);

    // 2. Добавление нового значения увеличивает размер коллекции на единицу.
    c1.add(10);
    assert(c1.size() == 1);

    // 3. Повторное добавление существующего значения не изменяет размер коллекции.
    c1.add(10);
    assert(c1.size() == 1);

    // 4. Удаление значения уменьшает размер коллекции на единицу.
    c1.remove(10);
    assert(c1.size() == 0);

    // 5. Пересечение с пустой коллекцией возвращает пустую коллекцию.
    Collection<int> c2;
    c2.add(1);
    c2.add(2);
    Collection<int> c3;
    Collection<int> intersection1 = c2 && c3;
    assert(intersection1.size() == 0);

    // 6. Пересечение одинаковых коллекций возвращает коллекцию, идентичную исходным.
    Collection<int> c4;
    c4.add(1);
    c4.add(2);
    c4.add(3);
    Collection<int> intersection2 = c4 && c4;
    assert(intersection2.size() == c4.size());
    assert(intersection2 == c4);

    // 7. Копия коллекции равна оригиналу до изменений.
    Collection<int> c5 = c4;
    assert(c5 == c4);
    c5.add(4);
    assert(!(c5 == c4));

    // 8. Сохранение коллекции в файл и загрузка из файла восстанавливает идентичное состояние.
    Collection<std::string> c6;
    c6.add("hello");
    c6.add("world");
    c6.saveToFile("test.bin");

    Collection<std::string> c7;
    c7.loadFromFile("test.bin");
    assert(c7.size() == c6.size());
    assert(c7 == c6);

    // Тест операторов << и []
    c7 << "extra";
    assert(c7.contains("extra"));
    c7["new_element"];
    assert(c7.contains("new_element"));
    c7.update("new_element", "changed_element");
    assert(c7.contains("changed_element"));

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}
