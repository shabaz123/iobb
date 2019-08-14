/******************************
 * test-inputs.c
 * v1.0 - shabaz - August 2019
 *
 * ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iobb.h>

#define EOA 0

char p8_output_pin=7; // set to the pin you want to be an output. All the rest will be inputs.
char level=1; // set to 1 for detecting a high level

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
    if (p8_array[i]!=p8_output_pin)
    {
      iolib_setdir(8,p8_array[i], DigitalIn);
    }
    else
    {
      iolib_setdir(8,p8_array[i], DigitalOut);
    }
    i++;
  }
  i=0;
  while(p9_array[i]!=EOA)
  {
    iolib_setdir(9,p9_array[i], DigitalIn);
    i++;
  }
}

void
code_out(char v)
{
  int i;
  int bit;
  int del=5;

  if (v<64)
  {
    printf("code out P8_%d\n", v);
  }
  else
  {
    printf("code out P9_%d\n", v-64);
  }

  for (bit=7; bit>=0; bit--)
  {
    if ((v & 1<<bit) || (bit==7))
    {
      pin_high(8, p8_output_pin);
    }
    else
    {
      pin_low(8, p8_output_pin);
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

int
main(int argc, char *argv[])
{
  char bit;
  int i;
  char val;
  int del=5;
  char found=0;

  if (argc>1)
  {
    if (argv[1][0]=='0')
    {
      printf("detecting low level\n");
      level=0;
    }
  }
  if (level==1)
  {
    printf("detecting high level\n");
  }


  init_gpio();

  while(1)
  {
    found=0;
    i=0;
    while(p8_array[i]!=EOA)
    {
      val=p8_array[i];
      if (val==p8_output_pin)
      {
        i++;
        val=p8_array[i];
      }
      if (level)
      {
        if (is_high(8, val))
        {
          found=1;
          code_out(val);
        }
      }
      else
      {
        if (is_low(8, val))
        {
          found=1;
          code_out(val);
        }
      }
      i++;
    }
    i=0;
    while(p9_array[i]!=EOA)
    {
      val=p9_array[i];
      if (level)
      {
        if (is_high(9, val))
        {
          found=1;
          code_out(val+64);
        }
      }
      else
      {
        if (is_low(9, val))
        {
          found=1;
          code_out(val+64);
        }
      }
      i++;
    }
    if (found==0)
    {
      code_out(0);
    }
    else
    {
      printf("\n");
    }
  }
  // warning on next line is ok
  return(0);
}

