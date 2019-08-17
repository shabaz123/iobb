/***************************
 * lcd3-test.c
 * 
 * Revision 0.1 April 2016 shabaz
 * Revision 1.0 August 2019 shabaz
 * Revision 1.1 August 2019 shabaz - added PocketBeagle code
 *
 * This is an I2C test program that can be used with the 
 * 3-digit LCD module design described here:
 * https://bit.ly/2Mh4kvp
 *
 ***************************/


#include <stdio.h>
#include "i2cfunc.h"

// set to 1 for PocketBeagle
#define POCKETBEAGLE 0


// we will use I2C2 which is enumerated as 2 on the BBB/PB (tested on both)
// Set to 1 to use I2CBUS1 (not tested on BBB. tested on PB)
#define I2CBUS 2

#define LCD_ADDR 0x38
// Four possible values for DEVICE_ADDRESS
// R1   R2   R3   R4   DEVICE_ADDRESS
// Fit       FIT       0x60
//      Fit  Fit       0x61
// Fit            Fit  0x62
//      Fit       Fit  0x63

// Commands (these can be 'continued' by setting the MSB
#define DEVICE_ADDR 0x60
#define BLINK_OFF 0x70
#define BANK_CMD 0x78

// BANK_CMD bit values
#define WR_BANK_A 0x00
#define WR_BANK_B 0x02
#define DISP_BANK_A 0x00
#define DISP_BANK_B 0x01

typedef struct char_prog_s
{
  unsigned char byte0;
  unsigned char byte1;
  unsigned char byte2;
} char_prog_t;

typedef struct ascii_s
{
  char_prog_t char0;
  char_prog_t char1;
  char_prog_t char2;
} ascii_t;

const char bit_table[]=
{
  0x38, 0x00, 0x86,    0x00, 0xbe, 0x00,    0x86, 0x00, 0x38,    /* 0 */
  0x08, 0x00, 0x02,    0x00, 0x0a, 0x00,    0x02, 0x00, 0x08,    /* 1 */
  0x30, 0x00, 0x46,    0x00, 0x76, 0x00,    0x46, 0x00, 0x30,    /* 2 */
  0x18, 0x00, 0x46,    0x00, 0x5e, 0x00,    0x46, 0x00, 0x18,    /* 3 */
  0x08, 0x00, 0xc2,    0x00, 0xca, 0x00,    0xc2, 0x00, 0x08,    /* 4 */
  0x18, 0x00, 0xc4,    0x00, 0xdc, 0x00,    0xc4, 0x00, 0x18,    /* 5 */
  0x38, 0x00, 0xc4,    0x00, 0xfc, 0x00,    0xc4, 0x00, 0x38,    /* 6 */
  0x08, 0x00, 0x06,    0x00, 0x0e, 0x00,    0x06, 0x00, 0x08,    /* 7 */
  0x38, 0x00, 0xc6,    0x00, 0xfe, 0x00,    0xc6, 0x00, 0x38,    /* 8 */
  0x18, 0x00, 0xc6,    0x00, 0xde, 0x00,    0xc6, 0x00, 0x18     /* 9 */
};

unsigned char buf[10];
int handle;
  
char_prog_t*
char_prog(int idx, unsigned char c)
{
  ascii_t *ascii_ptr;
  char_prog_t *char_prog_ptr;


  ascii_ptr=(ascii_t *)bit_table;
  char_prog_ptr=(char_prog_t *)(&ascii_ptr[c-'0']);
  return(&char_prog_ptr[idx]);
}

void
print_line(char* line)
{
  char line_idx=0;
  char lcd_idx=0;
  char not_finished=1;
  char c;
  char_prog_t *progval;
  unsigned char byte0=0;
  unsigned char byte1=0;
  unsigned char byte2=0;

  while(not_finished)
  {
    c=line[line_idx];
    switch(c)
    {
      case '.':
        // handle decimal point
        if (lcd_idx==1)
        {
          byte0 |= 0x01;
        }
        else if (lcd_idx==2)
        {
          byte1 |= 0x01;
        } 
        break;
      case ' ':
        lcd_idx++;
        if (lcd_idx>2)
        {
          not_finished=0;
        }
        break;
      case '\0':
        // line finished
        not_finished=0;
        break;
      default:
        if ((c<'0') || (c>'9'))
        {
          // we can't handle this char
        }
        else
        {
           progval=char_prog(lcd_idx, c);
           byte0=byte0 | progval->byte0;
           byte1=byte1 | progval->byte1;
           byte2=byte2 | progval->byte2;
           lcd_idx++;
           if (lcd_idx>2)
           {
             // we're done
             not_finished=0;
           }
        }
        break;
    } // end switch(c)
    line_idx++;
  } // end while(not_finished)

  buf[5]=byte0;
  buf[6]=byte1;
  buf[7]=byte2;
  i2c_write(handle, buf, 8);
}


int
main(void)
{
  int i;
  double v;
  unsigned char text[4];
  char_prog_t *progval;
  unsigned char mode, device, bank, blinkmode;

  printf("I2C bus selected: %d\n", I2CBUS);

  if (POCKETBEAGLE)
  {
    printf("PocketBeagle\n");
    if (I2CBUS==1)
    {
      configure_i2c_pins(9, 11); // P2 pins 9 (SCL) and 11 (SDA)
    }
    else if (I2CBUS==2)
    {
      configure_i2c_pins(28, 26); // P1 pins 28 (SCL) and 26 (SDA)
    }
  }
  else
  {
    printf("BeagleBone\n");
    if (I2CBUS==1)
    {
      printf("use other I2C bus : ) \n");
    }
    else if (I2CBUS==2)
    {
      configure_i2c_pins(19,20); // P9 pins 19 (SCL) and 20 (SDA)
    }
  }
  mode=0xc9; // Set static mode, display enabled, continuation enabled
  device=DEVICE_ADDR | 0x80; // Select the device, continuation enabled
  bank=BANK_CMD | 0x80 | WR_BANK_A | DISP_BANK_A; 
  blinkmode=BLINK_OFF | 0x80;
  buf[0]=mode;
  buf[1]=device;
  buf[2]=blinkmode;
  buf[3]=bank;
  buf[4]=0x00; // pointer

  handle=i2c_open(I2CBUS, 0x38);

  buf[5]=0xf1; // data
  buf[6]=0x80; // data
  buf[7]=0x02; // data

  progval=char_prog(0, '5');
  buf[5]=progval->byte0;
  buf[6]=progval->byte1;
  buf[7]=progval->byte2;

  //print_line(" . .");

  //delay_ms(999);  
  


  //for (i=0; i<1000; i++)
  for (v=0.0; v<99.9; v=v+0.1)
  {
    //sprintf(text, "%3d", i);
    sprintf(text, "%4.1f", v);
    print_line(text);
    delay_ms(40);
  }

  delay_ms(500);
  print_line("   ");


  i2c_close(handle);
  

  return(0);
}


