// spi_test.c
// rev 0.1 August 2019 shabaz

#include <stdio.h>
#include <iobb.h>

// set to 1 for PocketBeagle
#define POCKETBEAGLE 0

#define SPI_BUS SPI0

int
main(void)
{
  int i;
  unsigned int pin_direction;
  int rxval;
  int status;
  iolib_init();
  if (POCKETBEAGLE)
  {
    printf("PocketBeagle\n");
    if (SPI_BUS==SPI0)
    {
      configure_spi_pins_p1(); // SPI0 is on port P1 on PocketBeagle
    }
    else if (SPI_BUS==SPI1)
    {
      configure_spi_pins_p2(); // SPI1 is on port P2 on PocketBeagle
    }
  }
  else
  {
    printf("BeagleBone\n");
    if (SPI_BUS==SPI0)
    {
      configure_spi_pins(17, 18, 21, 22); // CS, D1, D0, CLK
    }
    else
    {
      printf("use other SPI bus : )\n"); // no other bus tested with BBB
    }
  }


  // MISO and MOSI pins are interchangeable depending on configuration
  // PocketBeagle has MISO and MOSI printed on the silkscreen, so this is set to match it
  if (POCKETBEAGLE)
    pin_direction=SPI_INOUT;
  else // Beaglebone has MISO and MOSI choice unallocated. This matches the demo code:
    pin_direction=SPI_OUTIN;


  if (POCKETBEAGLE)
    status=spi_enable_pb(SPI_BUS);
  else
    status=spi_enable(SPI_BUS);

  if (status)
  {
    spi_ctrl(SPI_BUS, SPI_CH0, SPI_MASTER, SPI_RX, /* use SPI_TX or SPI_RXTX depending on needs */
             SPI_DIV32, SPI_CLOCKMODE3, /* 48 MHz divided by 32, SPI mode 3 */
             		SPI_CE_ACT_LOW, pin_direction, 16); //16-bit transactions 
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

  if (POCKETBEAGLE)
    spi_disable_pb(SPI_BUS);
  else
    spi_disable(SPI_BUS);

  iolib_free();
  return(0);
}

