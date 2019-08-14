#include <stdio.h>
#include <iobb.h>

#define SPI_BUS SPI0

int
main(void)
{
  int i;
  int rxval;
  iolib_init();
  configure_spi_pins(17, 18, 21, 22); // CS, D1, D0, CLK
  if (spi_enable(SPI_BUS))
  {
    spi_ctrl(SPI_BUS, SPI_CH0, SPI_MASTER, SPI_RX, /* use SPI_TX or SPI_RXTX depending on needs */
             SPI_DIV32, SPI_CLOCKMODE3, /* 48 MHz divided by 32, SPI mode 3 */
             SPI_CE_ACT_LOW, SPI_OUTIN, 16); /* D0 is output and D1 is input, 16-bit transactions */
  }
  else
  {
    printf("error, spi is not enabled\n");
    iolib_free();
    return(1);
  }
  for (i=1; i<20; i++) 
  {
    spi_transact(SPI_BUS, SPI_CH0, 0 /*or integer to transmit data*/, &rxval);
    printf("Received: 0x%04x \n", rxval&0xffff);
    iolib_delay_ms(500);
  }
  spi_disable(SPI_BUS);
  iolib_free();
  return(0);
}

