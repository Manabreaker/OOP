#include "calculator.h"
#include "number.h"
#include <cassert>
#include <iostream>

void checkAndPrintStack(Calculator& calc) {
    std::cout << "Checking stack contents:" << std::endl;
    calc.printStack();
    std::cout << "------------------------------------" << std::endl;
}

int main() {
    Calculator calc;

    try {
        // Проверяем операцию с пустым стеком
        calc.performOperation("add");
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Добавляем числа
    calc.push(new ComplexNumber(1, 2));
    calc.push(new ComplexNumber(3, 4));

    // Проверяем сложение
    calc.performOperation("add");
    const auto* result = dynamic_cast<ComplexNumber*>(calc.pop());
    assert(result->getRealPart() == 4.0);
    assert(result->getImagPart() == 6.0);
    delete result;

    // Проверяем работу с кватернионами
    calc.push(new Quaternion(1, 1, 1, 1));
    calc.push(new Quaternion(2, 2, 2, 2));

    calc.performOperation("add");

    const auto* qResult = dynamic_cast<Quaternion*>(calc.pop());
    std::cout << qResult->getRealPart() << std::endl;
    checkAndPrintStack(calc);
    assert(qResult->getRealPart() == 3.0);
    assert(qResult->getIPart() == 3.0);
    assert(qResult->getJPart() == 3.0);
    assert(qResult->getKPart() == 3.0);
    delete qResult;

    // Проверяем типовые ошибки
    try {
        calc.push(new ComplexNumber(1, 2));
        calc.push(new Quaternion(1, 1, 1, 1));
        calc.performOperation("add");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        calc.performOperation("invalid_operation");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "All tests completed. Check errors if any." << std::endl;
    return 0;
}
