#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>

// Abstract class Number
class Number {
public:
    virtual ~Number() {}

    // Метод для идентификации типа числа
    virtual std::string getType() const = 0;
};

// Класс ComplexNumber
class ComplexNumber : public Number {
private:
    double realPart;
    double imagPart;

public:
    // Constructors
    ComplexNumber();
    ComplexNumber(double real, double imag);
    ComplexNumber(const ComplexNumber& other);

    // Getters
    double getRealPart() const;
    double getImagPart() const;

    // Setters
    void setRealPart(double real);
    void setImagPart(double imag);

    // Operations
    void add(const ComplexNumber& other);
    void subtract(const ComplexNumber& other);
    void multiply(const ComplexNumber& other);
    void divide(const ComplexNumber& other);

    // Identificator
    std::string getType() const override;
};

// Class Quaternion
class Quaternion : public Number {
private:
    double realPart;
    double iPart;
    double jPart;
    double kPart;

public:
    // Constructors
    Quaternion();
    Quaternion(double real, double i, double j, double k);
    Quaternion(const Quaternion& other);

    // Getters
    double getRealPart() const;
    double getIPart() const;
    double getJPart() const;
    double getKPart() const;

    // Setters
    void setRealPart(double real);
    void setIPart(double i);
    void setJPart(double j);
    void setKPart(double k);

    // Operations
    void add(const Quaternion& other);
    void subtract(const Quaternion& other);
    void multiply(const Quaternion& other);
    void divide(const Quaternion& other);

    // Identificator
    std::string getType() const override;
};

#endif // NUMBER_H
