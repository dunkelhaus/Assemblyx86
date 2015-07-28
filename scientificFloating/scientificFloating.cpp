// Author: Kumud Ravisankaran
// Author: Suraj Jena
#include <iostream>

using namespace std;

int main()
{
  float f; 
  cout << "Please enter a float: ";
  cin >> f;

  if(f == 0) // if f == 0
  {
    cout << "0E0" << endl;
    return 0;
  } // if

  unsigned int float_int = *((unsigned int *)&f);
  unsigned int sign, exponent, m[23]; 
  sign = float_int >> 31;
  exponent = float_int & 0x7f800000;
  exponent >>= 23;

  for (int i = 22; i >= 0; i--)
    m[(22 - i)] = ((float_int >> i)&1);

  for (int i = 0; i <= 22; i++)
  { 
    if (m[i] == 0) // if
    {
      int count = 0;
      for (int j = i; j <= 22; j++)
        if ( m[j] == 1) // if
          count++;
      if (count == 0) // if
        m[i] = 2;
    } // if
  } // for

  if (exponent != 0)
    exponent = exponent - 127;

  if (sign != 1)
  {
    sign = sign + 1;
    cout << sign << ".";
  } // if

  else 
  {
    cout << "-" << sign << ".";
  } // else
  for (int i = 0; i <= 22; i++)
  {
    if (m[i] == 0 || m[i] == 1)
    { 
       cout << m[i];
    } // if
  } // for

  cout << "E" << exponent << endl;
  return 0;
} // main
