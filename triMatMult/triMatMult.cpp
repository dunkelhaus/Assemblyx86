// Author: Suraj Jena
// Author: Kumud Ravisankaran
#include <iostream>
#include <fstream>

using namespace std;

void print(int result[], int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << result[i] << endl;
  }
}

int demarcValue(int index, int runc)
{
  int curval = 0;

  for (int i = 0; i < runc; i++)
    curval += (index - i);

  return curval;
} // demarcValue

void matrixMultiply(int index, int set1[], int set2[], int length)
{ 
  int demarc1 = 0;
  int demarc2 = 0;
  int result[length];
  for (int l = 0; l < index; l++)
  {
    demarc2 = demarcValue(index, (l + 1));
    for (int i = demarc1; i < demarc2; i++)
    {
      int element = 0;
      int k = demarc1;
      int k2 = i;
      int count = 0;
      for (int j = demarc2 - (demarc2 - 1 - i); j > demarc1; j--)
      {
        element += (set1[k] * set2[k2]);
        k2 += (index - l - 1 - count);
        k++;
        count++;
      }
      result[i] = element;
    }
    demarc1 = demarc2;
  }
  print(result, length);
} // matrixMultiply
    
void workHorse(char* arguments[])
{
  int index = 0;
  int length = 0;
  ifstream file1(arguments[1]);
  file1 >> index; 
  for (int i = index; i > 0; i--)
    length += i;
  
  int set1[length];
  int set2[length];
  for (int i = 0; i < length; i++)
    file1 >> set1[i];
  ifstream file2(arguments[2]);
  file2 >> index;
  for (int i = 0; i < length; i++)
    file2 >> set2[i];

  matrixMultiply(index, set1, set2, length);
}

int main(int argCount, char* arguments[])
{
  workHorse(arguments);
  return 0;
} // int main
