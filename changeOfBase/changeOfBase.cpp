// Author: Suraj Jena
// Author: Kumud Ravisankaran
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

char* strrev(char* str)
{
  int length = strlen(str);
  int j = 0;
  char* rev = new char[length + 1];
  for (int i = length - 1; i >= 0; i--)
  {
    rev[j] = str[i];
    j++;
  }
  
  return rev;
}

long toDefaultBase(short base, char* num)
{
  int length = strlen(num);
  int number[33];
  int chrep = 0;
  int multiple = 0;
  long result = 0;
  int i = 0;
  for (i = 0; i < length; i++)
  {
    chrep = char(num[i]);

    if (chrep < 58) // if is digit
      number[i] = chrep - 48;
    else
      number[i] = chrep - 55;

  } // for
  
  for (int i = 0; i < length; i++)
  {
    int reverse = length - i - 1;
    multiple = int(pow(double(base), double(i)));
    result += (number[reverse] * multiple);
  }
  
  return result;
}
 
char* toTargetBase(long num, short base2)
{
  int rem = 0;
  int i = 0;
  char* result = new char[33];
  while (true)
  {
    rem = num % base2;
    num = num / base2;
    if (rem > 9)
      result[i] = char(rem + 55);
    else
      result[i] = char(rem + 48);

    i++;

    if (num == 0)
      break;
  }
  
  result = strrev(result);
  return result;
}

void print(short base, short base2, char* number, char* result)
{
  cout << number << " base " << base << " is " 
       << result << " base " << base2 << endl;
}

void processCommand()
{
  long defbase = 0;
  char* result = new char[33];
  short base = 0;
  short base2 = 0;
  char* num = new char[33];
  cout << "Please enter the number's base: ";
  cin >> base;
  cin.ignore(256, '\n');
  cout << "Please enter the number: ";
  cin >> num;
  cin.ignore(256, '\n');
  cout << "Please enter the new base: ";
  cin >> base2;
  cin.ignore(256, '\n');
  defbase = toDefaultBase(base, num);
  result = toTargetBase(defbase, base2);
  print(base, base2, num, result);
} // processCommand

int main()
{
  processCommand();
  return 0;
} // main()
