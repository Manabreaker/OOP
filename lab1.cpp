#include <iostream>
#include <cassert>

class ComplexNumber {
private:
    double realPart;
    double imagPart;

public:
    // Default constructor
    ComplexNumber() : realPart(0.0), imagPart(0.0) {}

    // Initialization constructor
    ComplexNumber(double real, double imag) : realPart(real), imagPart(imag) {}

    // Copy constructor
    ComplexNumber(const ComplexNumber& other): realPart(other.realPart), imagPart(other.imagPart) {}

    // Accessors (getters)
    double getRealPart() const {
        return realPart;
    }

    double getImagPart() const {
        return imagPart;
    }

    // Mutators (setters)
    void setRealPart(double real) {
        realPart = real;
    }

    void setImagPart(double imag) {
        imagPart = imag;
    }

	void add(const ComplexNumber& other) {
		realPart += other.realPart;
		imagPart += other.imagPart;
	}

	void subtract(const ComplexNumber& other) {
		realPart -= other.realPart;
		imagPart -= other.imagPart;
	}

	void multiply(const ComplexNumber& other) {
		double tempReal = realPart * other.realPart - imagPart * other.imagPart;
		double tempImag = realPart * other.imagPart + imagPart * other.realPart;
		realPart = tempReal;
		imagPart = tempImag;
	}

	void divide(const ComplexNumber& other) {
		double tempReal = (realPart * other.realPart + imagPart * other.imagPart) / (other.realPart * other.realPart + other.imagPart * other.imagPart);
		double tempImag = (imagPart * other.realPart - realPart * other.imagPart) / (other.realPart * other.realPart + other.imagPart * other.imagPart);
		realPart = tempReal;
		imagPart = tempImag;
	}

};

int main() {
    // Test default constructor
    ComplexNumber cn1;
    assert(cn1.getRealPart() == 0.0);
    assert(cn1.getImagPart() == 0.0);

    // Test initialization constructor
    ComplexNumber cn2(3.0, 4.0); // 3 + 4i
    assert(cn2.getRealPart() == 3.0);
    assert(cn2.getImagPart() == 4.0);

    // Test copy constructor
    ComplexNumber cn3(cn2); // копируем cn2 (3 + 4i)
    assert(cn3.getRealPart() == 3.0);
    assert(cn3.getImagPart() == 4.0);

    // Test setters
    cn1.setRealPart(5.0);
    cn1.setImagPart(6.0);
    assert(cn1.getRealPart() == 5.0);
    assert(cn1.getImagPart() == 6.0);

    // Test add
    cn1.add(cn2); // 5 + 6i + 3 + 4i = 8 + 10i
    assert(cn1.getRealPart() == 8.0);
    assert(cn1.getImagPart() == 10.0);

    // Test subtract
    cn3.subtract(cn2); // (3 + 4i) - (3 + 4i) = 0 + 0i
    assert(cn3.getRealPart() == 0.0);
    assert(cn3.getImagPart() == 0.0);

    // Test multiply
    ComplexNumber cn4(1.0, 2.0); // 1 + 2i
    ComplexNumber cn5(3.0, 4.0); // 3 + 4i
    cn4.multiply(cn5);           // (1 + 2i) * (3 + 4i) = -5 + 10i
    assert(cn4.getRealPart() == -5.0);
    assert(cn4.getImagPart() == 10.0);

    // Test divide
    ComplexNumber cn6(3.0, 4.0);  // 3 + 4i
    ComplexNumber cn7(1.0, 2.0);  // 1 + 2i
    cn6.divide(cn7);              // (3 + 4i) / (1 + 2i) = 2.2 - 0.4i
    assert(cn6.getRealPart() == 2.2);
    assert(cn6.getImagPart() == -0.4);

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

