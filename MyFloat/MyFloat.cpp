#include "MyFloat.h"

MyFloat::MyFloat(){
    sign = 0;
    exponent = 0;
    mantissa = 0;
}

MyFloat::MyFloat(float f){
    unpackFloat(f);
}

MyFloat::MyFloat(const MyFloat & rhs){
	sign = rhs.sign;
	exponent = rhs.exponent;
	mantissa = rhs.mantissa;
}

ostream& operator<<(std::ostream &strm, const MyFloat &f){
	strm << f.packFloat();
	return strm;
}

bool operator==(const MyFloat& lhs, const float& rhs){
    return lhs.packFloat() == rhs;
}

MyFloat MyFloat::normalizeExponent(unsigned int newExponent) const{
    MyFloat normalizedVal(*this);

    // increase precision by moving the mantissa to the left
    normalizedVal.mantissa = normalizedVal.mantissa<<7;
    //add back the 1 at the start
    normalizedVal.mantissa |= (1<<30);

    unsigned int shift = newExponent - normalizedVal.exponent;
    normalizedVal.mantissa = shift > 23 ? 0 : (normalizedVal.mantissa >> shift);
    normalizedVal.exponent = newExponent;
    return normalizedVal;
}

void MyFloat::normalize() {
    if(mantissa == 0) {
        sign = 0;
        exponent = 0;
        return;
    }
    mantissa = mantissa >> 7;
    unsigned int carry = mantissa >> 23;
    if(carry > 1) {
        while(carry > 1) {
            mantissa = mantissa >> 1;
            exponent++;
            carry = carry >> 1;
        }
    }
    else if(carry == 0) {
        while(carry == 0) {
            mantissa = mantissa << 1;
            exponent--;
            carry = mantissa >> 23;
        }
    }
    mantissa = mantissa & ~(1<<23);
}

MyFloat MyFloat::operator+(const MyFloat& rhs) const{
    unsigned int maxExponent = rhs.exponent > exponent ? rhs.exponent : exponent;
    MyFloat a = normalizeExponent(maxExponent);
    MyFloat b = rhs.normalizeExponent(maxExponent);

    MyFloat result;
    result.exponent = maxExponent;
    if(a.sign == b.sign)
    {
        result.mantissa = (a.mantissa + b.mantissa);
        result.sign = a.sign;
    }
    else
    {
        if(a.mantissa > b.mantissa) {
            result.mantissa = (a.mantissa - b.mantissa);
            result.sign = a.sign;
        }
        else {
            result.mantissa = (b.mantissa - a.mantissa);
            result.sign = b.sign;
        }
        if(result.mantissa == 0)
            result.sign = 0;
    }

    result.normalize();
	return result;
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{
    MyFloat rhsSigned(rhs);
    rhsSigned.sign = !rhsSigned.sign;
    return *this + rhsSigned;
}

void MyFloat::unpackFloat(float f) {
    __asm__(
        "mov %3, %%ebx;\n\t"
        "mov %%ebx, %%eax;\n\t"
        "and $0x7FFFFF,%%eax;\n\t"
        "mov %%eax, %0;\n\t"
        "mov %%ebx, %%eax;\n\t"
        "and $0x7F800000,%%eax;\n\t"
        "shr $23, %%eax;\n\t"
        "mov %%eax, %1;\n\t"
        "mov %%ebx, %%eax;\n\t"
        "shr $31, %%eax;\n\t"
        "mov %%eax, %3;\n\t"
        :"=r"(mantissa), "=r"(exponent), "=r"(sign)      /* output */
        :"r"(f)                                          /* input */
        :"%eax", "%ebx"                                  /* clobbered register */
    );

}//unpackFloat

float MyFloat::packFloat() const{
    float f = 0;
    __asm__(
        "mov %1, %%ebx;\n\t"
        "mov %2, %%eax;\n\t"
        "shl $31,%%eax;\n\t"
        "or  %%eax, %%ebx;\n\t"
        "mov %3, %%eax;\n\t"
        "shl $23,%%eax;\n\t"
        "or  %%eax, %%ebx;\n\t"
        "mov %%ebx, %0;\n\t"
        :"=r"(f)                                         /* output */
        :"r"(mantissa), "r"(sign), "r"(exponent)         /* input */
        :"%eax", "%ebx"                                  /* clobbered register */
    );
    return f;
}//packFloat

bool MyFloat::carryWouldHappen(unsigned int a, unsigned int b){
    int carry;
    __asm__("mov %1, %%eax;\n\t"
          "adc %%eax, %2;\n\t"
          "sbb %%eax, %%eax;\n\t"
          "mov %%eax, %0;"
         :"=r"(carry)                /* output */
         :"r"(a), "r"(b)             /* input */
         :"%eax"                     /* clobbered register */
         );
    return carry == -1;
}//carryWouldHappen


