#include "Number.h"
#include <cassert>

int main() {
    // Test ComplexNumber
    ComplexNumber cn1;
    assert(cn1.getRealPart() == 0.0);
    assert(cn1.getImagPart() == 0.0);
    assert(cn1.getType() == "ComplexNumber");

    ComplexNumber cn2(3.0, 4.0);
    assert(cn2.getRealPart() == 3.0);
    assert(cn2.getImagPart() == 4.0);

    ComplexNumber cn3(cn2);
    assert(cn3.getRealPart() == 3.0);
    assert(cn3.getImagPart() == 4.0);

    cn1.setRealPart(5.0);
    cn1.setImagPart(6.0);
    assert(cn1.getRealPart() == 5.0);
    assert(cn1.getImagPart() == 6.0);

    // Test Quaternion
    Quaternion q1;
    assert(q1.getRealPart() == 0.0);
    assert(q1.getIPart() == 0.0);
    assert(q1.getJPart() == 0.0);
    assert(q1.getKPart() == 0.0);
    assert(q1.getType() == "Quaternion");

    Quaternion q2(1.0, 2.0, 3.0, 4.0);
    assert(q2.getRealPart() == 1.0);
    assert(q2.getIPart() == 2.0);
    assert(q2.getJPart() == 3.0);
    assert(q2.getKPart() == 4.0);

    Quaternion q3(q2);
    assert(q3.getRealPart() == 1.0);
    assert(q3.getIPart() == 2.0);
    assert(q3.getJPart() == 3.0);
    assert(q3.getKPart() == 4.0);

    q1.setRealPart(5.0);
    q1.setIPart(6.0);
    q1.setJPart(7.0);
    q1.setKPart(8.0);
    assert(q1.getRealPart() == 5.0);
    assert(q1.getIPart() == 6.0);
    assert(q1.getJPart() == 7.0);
    assert(q1.getKPart() == 8.0);

    q1.add(q2);
    assert(q1.getRealPart() == 6.0);
    assert(q1.getIPart() == 8.0);
    assert(q1.getJPart() == 10.0);
    assert(q1.getKPart() == 12.0);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
