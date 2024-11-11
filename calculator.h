#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Number.h"
#include <stack>
#include <string>

class Calculator {
private:
    std::stack<Number*> stack;

    // Вспомогательная функция для выполнения бинарной операции
    void executeBinaryOperation(
        Number* num1, Number* num2,
        void (ComplexNumber::*complexOp)(const ComplexNumber&),
        void (Quaternion::*quaternionOp)(const Quaternion&)
    );

public:
    ~Calculator();

    // Добавление числа в стек
    void push(Number* number);

    // Удаление числа из стека
    Number* pop();

    // Выполнение арифметической операции
    void performOperation(const std::string& operation);

    // Печать содержимого стека
    void printStack() const;
};

#endif // CALCULATOR_H
