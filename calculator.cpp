#include "calculator.h"
#include <iostream>
#include <stdexcept>

// Деструктор: очищает стек и освобождает память
Calculator::~Calculator() {
    while (!stack.empty()) {
        delete stack.top();
        stack.pop();
    }
}

// Добавить элемент в стек
void Calculator::push(Number* number) {
    stack.push(number);
}

// Извлечь элемент из стека
Number* Calculator::pop() {
    if (stack.empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    Number* top = stack.top();
    stack.pop();
    return top;
}

// Выполнить операцию
void Calculator::performOperation(const std::string& operation) {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough elements in the stack.");
    }

    Number* num2 = pop();
    Number* num1 = pop();

    try {
        if (operation == "add") {
            executeBinaryOperation(num1, num2, &ComplexNumber::add, &Quaternion::add);
        } else if (operation == "subtract") {
            executeBinaryOperation(num1, num2, &ComplexNumber::subtract, &Quaternion::subtract);
        } else if (operation == "multiply") {
            executeBinaryOperation(num1, num2, &ComplexNumber::multiply, &Quaternion::multiply);
        } else if (operation == "divide") {
            executeBinaryOperation(num1, num2, &ComplexNumber::divide, &Quaternion::divide);
        } else {
            throw std::runtime_error("Unsupported operation: " + operation);
        }
    } catch (...) {
        // Освободить память в случае ошибки
        delete num1;
        delete num2;
        throw;
    }

    // Если операция успешна, num1 уже возвращено в стек
    delete num2;
}

// Вспомогательная функция для выполнения операций
void Calculator::executeBinaryOperation(
    Number* num1, Number* num2,
    void (ComplexNumber::*complexOp)(const ComplexNumber&),
    void (Quaternion::*quaternionOp)(const Quaternion&)
) {
    if (auto* c1 = dynamic_cast<ComplexNumber*>(num1)) {
        if (auto* c2 = dynamic_cast<ComplexNumber*>(num2)) {
            (c1->*complexOp)(*c2);
            push(c1);
            return;
        }
    }

    if (auto* q1 = dynamic_cast<Quaternion*>(num1)) {
        if (auto* q2 = dynamic_cast<Quaternion*>(num2)) {
            (q1->*quaternionOp)(*q2);
            push(q1);
            return;
        }
    }

    // Если типы не совпадают
    throw std::runtime_error("Mismatched types or unsupported operation.");
}

// Вывести содержимое стека
void Calculator::printStack() const {
    std::stack<Number*> tempStack = stack;
    std::cout << "Stack contents (top to bottom):\n";
    while (!tempStack.empty()) {
        auto* number = tempStack.top();
        std::cout << " - " << number->getType() << "\n";
        tempStack.pop();
    }
}
