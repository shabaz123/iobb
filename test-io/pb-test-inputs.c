/******************************
 * pb-test-inputs.c (for PocketBeagle)
 * v1.0 - shabaz - August 2019
 *
 * ****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iobb.h>

#define EOA 0

char p2_output_pin=4; // set to the pin you want to be an output. All the rest will be inputs.
char level=1; // set to 1 for detecting a high level

char p1_array[]={2, 4, 6, 8, 10, 12, 20, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, EOA};
char p2_array[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 17, 18, 19, 20, 22, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34, 35, EOA};


void
init_gpio(void)
{
  int i;

  iolib_init();
  i=0;

  while(p1_array[i]!=EOA)
  {
    iolib_setdir(1,p1_array[i], DigitalIn);
    i++;
  }
  i=0;
  while(p2_array[i]!=EOA)
  {
    if (p2_array[i]!=p2_output_pin)
    {
      iolib_setdir(2,p2_array[i], DigitalIn);
    }
    else
    {
      iolib_setdir(2,p2_array[i], DigitalOut);
    }
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
    printf("code out P1_%d\n", v);
  }
  else
  {
    printf("code out P2_%d\n", v-64);
  }

  for (bit=7; bit>=0; bit--)
  {
    if ((v & 1<<bit) || (bit==7))
    {
      pin_high(2, p2_output_pin);
    }
    else
    {
      pin_low(2, p2_output_pin);
    }
    iolib_delay_ms(del);
  }
#ifdef dontdo
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
#endif
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
    while(p1_array[i]!=EOA)
    {
      val=p1_array[i];
      if (level)
      {
        if (is_high(1, val))
        {
          found=1;
          code_out(val);
        }
      }
      else
      {
        if (is_low(1, val))
        {
          found=1;
          code_out(val);
        }
      }
      i++;
    }
    i=0;
    while(p2_array[i]!=EOA)
    {
      val=p2_array[i];
      if (val==p2_output_pin)
      {
        i++;
        val=p2_array[i];
      }
      if (level)
      {
        if (is_high(2, val))
        {
          found=1;
          code_out(val+64);
        }
      }
      else
      {
        if (is_low(2, val))
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

