/******************************
 * pb-test-outputs.c
 * v1.0 - shabaz - August 2019
 *
 * ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iobb.h>

#define EOA 0
char p1_array[]={2, 4, 20, 34, EOA};
char p2_array[]={2, 3, 4, 6, 8, 10, 17, 18, 19, 20, 22, 24, 33, 35, EOA};


void
init_gpio(void)
{
  int i;

  iolib_init();
  i=0;
  while(p1_array[i]!=EOA)
  {
    iolib_setdir(1,p1_array[i], DigitalOut);
    i++;
  }
  i=0;
  while(p2_array[i]!=EOA)
  {
    iolib_setdir(2,p2_array[i], DigitalOut);
    i++;
  }
}

int
main(void)
{
  int bit;
  int i;
  char val;
  int del=5;

  init_gpio();
  
  while(1)
  {
    for (bit=7; bit>=0; bit--)
    {
      i=0;
      while(p1_array[i]!=EOA)
      {
        val=p1_array[i];
        if ((val & 1<<bit) || (bit==7))
        {
          pin_high(1, val);
        }
        else
        {
          pin_low(1, val);
        }
        i++;
      }
      i=0;
      while(p2_array[i]!=EOA)
      {
        val=p2_array[i];
        if ((val & 1<<bit) || (bit==7))
        {
          pin_high(2, val);
        }
        else
        {
          pin_low(2, val);
        }
        i++;
      }
      iolib_delay_ms(del);
    }
    i=0;
    while(p1_array[i]!=EOA)
    {
      pin_low(1, p1_array[i]);
      i++;
    }
    i=0;
    while(p2_array[i]!=EOA)
    {
      pin_low(2, p2_array[i]);
      i++;
    }

    iolib_delay_ms(100);
  }


  // warning on next line is ok
  return(0);
}

