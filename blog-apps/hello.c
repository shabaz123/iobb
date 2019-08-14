#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <iobb.h>

int not_finished=1;

void
check_root_user(void)
{
  if(geteuid()!=0)
    printf("Run as root user! (or use sudo)\n");
}

void
ctrl_c_handler(int dummyvar)
{
  not_finished=0;
}

int
main(void)
{
  signal (SIGINT, ctrl_c_handler);
  check_root_user();
  iolib_init();
  iolib_setdir(8, 12, DigitalOut);
  while(not_finished)
  {
    pin_high(8, 12);
    iolib_delay_ms(500);
    pin_low(8, 12);
    iolib_delay_ms(500);
  }

  printf("\nBye\n");
  iolib_free();
  return(0);
}

