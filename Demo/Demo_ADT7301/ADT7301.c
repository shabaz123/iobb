/* ADT7301 Digital Temperature Sensor .
 *	Simple demo for SPI modules in BBBio library ,	Read temperature per second .
 *
 *	1. Please check the PIN status of SPI-1 in BBB , if your PIN status not in SPI mode ,
 *		 please follow "overlay" step in README.md to load BBBIO-SPI1 .
 *
 *	2. CircuitLayout in Demo/Demo_ADT7301/CircuitLayout_ADT7301.png
 */
/* ----------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../BBBio_lib/BBBiolib.h"
/* ------------------------------------------------------------------------ */
int main(void)
{
	int Rx_temp = 0;
	int i = 0;

	iolib_init();

	if(spi_enable(SPI0)) {
		spi_ctrl(SPI0 ,
				SPI_CH0 ,
				SPI_MASTER ,
				SPI_RX ,		
				SPI_DIV32 ,		/* 48Mhz div 32 as SPI speed */
				SPI_CLOCKMODE3 ,		/* CLK active low and sampling occurs on the rising edge */
				SPI_CE_ACT_LOW ,	/* CS/En pin low when active */
				SPI_OUTIN ,		/* data0 output , data1 input */
				16);				/* 16 bit TxRx per work */

		for(i = 0 ; i < 20 ; i++) {
			spi_transact(SPI0, SPI_CH0, 0, &Rx_temp);
			Rx_temp &= 0x0FFFF;
			printf("spi recv, Raw : %X ,Temperature %f\n", Rx_temp, Rx_temp / 32.0f);
			sleep(1);
		}
		spi_disable(SPI0);
	}
	else {
		printf("SPI init failed\n");
	}
	iolib_free();
	return 0 ;
}
