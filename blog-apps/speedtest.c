#include <stdio.h>
#include <unistd.h>
#include <iobb.h>

void
check_root_user(void)
{
  if(geteuid()!=0)
    printf("Run as root user! (or use sudo)\n");
}

int
main(void)
{
  check_root_user();
  iolib_init();
  iolib_setdir(8, 12, DigitalOut);
  while(1)
  {
    pin_high(8, 12);
    pin_low(8, 12);
  }
  return(0);
}

