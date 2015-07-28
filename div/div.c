#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

unsigned long no_bits(unsigned long val)
{
 int i =0; unsigned long count =0;
 for( i= 0; i < 32 ; i++)
 { 
   count ++;
   if(val == 0)
     return count;
   else
   val = val >> 1;
 }
 return 32;
}
//printf("%u", count);
//char ch = getchar();
 
unsigned int division(unsigned long dividend, unsigned int divisor, unsigned int *remainder)
{
 
 unsigned int  quotient =0;
 *remainder= 0;
 unsigned long nbits= no_bits(dividend);
  printf("nbits: %lu\n", nbits);
 int i=0;
 for(i= nbits -1 ; i >=0; i--)
 {
    printf("I: %d\n", i);
   *remainder = *remainder << 1;
    printf("Remainder: %u\n", *remainder);
    printf("Dividend (change test 1): %lu\n", dividend);
    unsigned long bit= (dividend >> i) &1;
    printf("Dividend (change test 2): %lu\n", dividend);
    printf("Bit: %lu\n", bit);
    *remainder |= bit << 0;
    printf("Remainder (2nd occurence): %u\n", *remainder);
    if( *remainder >= divisor)
    {
      *remainder= *remainder - divisor;
       quotient|= 1<< i;
       printf("Remainder (3rd occurence; %u\n", *remainder);
       printf("Quotient: %u\n", quotient);
    } 
}

return quotient;


}

int main (int argc , char **argv)
{
  unsigned long dvd;
  unsigned int div;
  unsigned int remainder=0;
 // printf("here1");
  dvd = atoll(argv[1]);
  div = atoi(argv[2]);
  unsigned int result;
  printf("%lu / %u = ", dvd , div);
  
  result = division(dvd, div, &remainder);
  printf("%u R %u\n" , result , remainder); 
  return 0; 
 } 
