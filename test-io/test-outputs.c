/******************************
 * test-outputs.c
 * v1.0 - shabaz - August 2019
 *
 * ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iobb.h>

#define EOA 0
char p8_array[]={7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 26, EOA};
char p9_array[]={11, 12, 13, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 41, 42, EOA};


void
init_gpio(void)
{
  int i;

  iolib_init();
  i=0;
  while(p8_array[i]!=EOA)
  {
    iolib_setdir(8,p8_array[i], DigitalOut);
    i++;
  }
  i=0;
  while(p9_array[i]!=EOA)
  {
    iolib_setdir(9,p9_array[i], DigitalOut);
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
      while(p8_array[i]!=EOA)
      {
        val=p8_array[i];
        if ((val & 1<<bit) || (bit==7))
        {
          pin_high(8, val);
        }
        else
        {
          pin_low(8, val);
        }
        i++;
      }
      i=0;
      while(p9_array[i]!=EOA)
      {
        val=p9_array[i];
        if ((val & 1<<bit) || (bit==7))
        {
          pin_high(9, val);
        }
        else
        {
          pin_low(9, val);
        }
        i++;
      }
      iolib_delay_ms(del);
    }
    i=0;
    while(p8_array[i]!=EOA)
    {
      pin_low(8, p8_array[i]);
      i++;
    }
    i=0;
    while(p9_array[i]!=EOA)
    {
      pin_low(9, p9_array[i]);
      i++;
    }

    iolib_delay_ms(100);
  }


  // warning on next line is ok
  return(0);
}

