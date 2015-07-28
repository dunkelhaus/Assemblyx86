#ifndef MY_FLOAT_H
    #define MY_FLOAT_H
  
    #include <iostream>
    using namespace std;
  
    class MyFloat {
        public:
            //constructors
            MyFloat();
            MyFloat(float f);
            MyFloat(const MyFloat & rhs);
            virtual ~MyFloat() {};
      
            //output
            friend ostream& operator<<(std::ostream& strm, const MyFloat& f);

            //comparison
            friend bool operator==(const MyFloat& lhs, const float& rhs);

            //addition
            MyFloat operator+(const MyFloat& rhs) const;

            //subtraction
            MyFloat operator-(const MyFloat& rhs) const;
    
        private:
            unsigned int sign;
            unsigned int exponent;
            unsigned int mantissa;


            void unpackFloat(float f);
            float packFloat() const;
            void printBits(unsigned int d) const;
            void printBits() const;

            static bool carryWouldHappen(unsigned int a, unsigned int b);
            MyFloat normalizeExponent(unsigned int exponent) const;
            void normalize();
    };
  
  
#endif
