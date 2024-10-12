#include "Number.h"

// ComplexNumber Methods
// Constructors
ComplexNumber::ComplexNumber() : realPart(0.0), imagPart(0.0) {}
ComplexNumber::ComplexNumber(double real, double imag) : realPart(real), imagPart(imag) {}
ComplexNumber::ComplexNumber(const ComplexNumber& other) : realPart(other.realPart), imagPart(other.imagPart) {}

// Getters
double ComplexNumber::getRealPart() const {
    return realPart;
}

double ComplexNumber::getImagPart() const {
    return imagPart;
}

// Setters
void ComplexNumber::setRealPart(double real) {
    realPart = real;
}

void ComplexNumber::setImagPart(double imag) {
    imagPart = imag;
}

// Operations
void ComplexNumber::add(const ComplexNumber& other) {
    realPart += other.realPart;
    imagPart += other.imagPart;
}

void ComplexNumber::subtract(const ComplexNumber& other) {
    realPart -= other.realPart;
    imagPart -= other.imagPart;
}

void ComplexNumber::multiply(const ComplexNumber& other) {
    double tempReal = realPart * other.realPart - imagPart * other.imagPart;
    double tempImag = realPart * other.imagPart + imagPart * other.realPart;
    realPart = tempReal;
    imagPart = tempImag;
}

void ComplexNumber::divide(const ComplexNumber& other) {
    double denom = other.realPart * other.realPart + other.imagPart * other.imagPart;
    double tempReal = (realPart * other.realPart + imagPart * other.imagPart) / denom;
    double tempImag = (imagPart * other.realPart - realPart * other.imagPart) / denom;
    realPart = tempReal;
    imagPart = tempImag;
}

// Identificator
std::string ComplexNumber::getType() const {
    return "ComplexNumber";
}

// Quaternion Methods
// Constructors
Quaternion::Quaternion() : realPart(0.0), iPart(0.0), jPart(0.0), kPart(0.0) {}
Quaternion::Quaternion(double real, double i, double j, double k) : realPart(real), iPart(i), jPart(j), kPart(k) {}
Quaternion::Quaternion(const Quaternion& other) : realPart(other.realPart), iPart(other.iPart), jPart(other.jPart), kPart(other.kPart) {}

// Getters
double Quaternion::getRealPart() const {
    return realPart;
}

double Quaternion::getIPart() const {
    return iPart;
}

double Quaternion::getJPart() const {
    return jPart;
}

double Quaternion::getKPart() const {
    return kPart;
}

// Setters
void Quaternion::setRealPart(double real) {
    realPart = real;
}

void Quaternion::setIPart(double i) {
    iPart = i;
}

void Quaternion::setJPart(double j) {
    jPart = j;
}

void Quaternion::setKPart(double k) {
    kPart = k;
}

// Operations
void Quaternion::add(const Quaternion& other) {
    realPart += other.realPart;
    iPart += other.iPart;
    jPart += other.jPart;
    kPart += other.kPart;
}

void Quaternion::subtract(const Quaternion& other) {
    realPart -= other.realPart;
    iPart -= other.iPart;
    jPart -= other.jPart;
    kPart -= other.kPart;
}

void Quaternion::multiply(const Quaternion& other) {
    const double tempReal = realPart * other.realPart - iPart * other.iPart - jPart * other.jPart - kPart * other.kPart;
    const double tempI = realPart * other.iPart + iPart * other.realPart + jPart * other.kPart - kPart * other.jPart;
    const double tempJ = realPart * other.jPart + jPart * other.realPart + kPart * other.iPart - iPart * other.kPart;
    const double tempK = realPart * other.kPart + kPart * other.realPart + iPart * other.jPart - jPart * other.iPart;
    realPart = tempReal;
    iPart = tempI;
    jPart = tempJ;
    kPart = tempK;
}

void Quaternion::divide(const Quaternion& other) {
    // Упрощённая версия деления для кватернионов
    // Реализовать точное деление можно через сопряжение и модуль
    realPart /= other.realPart;
    iPart /= other.iPart;
    jPart /= other.jPart;
    kPart /= other.kPart;
}

// Identificator
std::string Quaternion::getType() const {
    return "Quaternion";
}
