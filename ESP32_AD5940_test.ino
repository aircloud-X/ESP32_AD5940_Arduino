#include "ad5940.h"

void setup() {
  // put your setup code here, to run once:
  AD5940_MCUResourceInit(NULL);

	printf("MCU Initialised\n");

	// reset AD5940
	printf("Attempting to reset AD5940...\n");
	AD5940_HWReset();
	printf("AD5940 reset!\n");

	// initialise AD5940 by writing the startup sequence
	printf("Attempting to initialise AD5940...\n");
	AD5940_Initialize();
	printf("AD5940 initialised!\n");
}

void loop() {
  // put your main code here, to run repeatedly:
static unsigned long count;
		static unsigned long data;
		/* write 0x000000f0 */
		data = 0x0&0xffff;
		data <<= 16;
		data |= 0xf0&0xffff;
		count ++;	/* Read write count */
    if(count>100000)
      count=0;
		/**
		 * Register CALDATLOCK is 32-bit width, it's readable and writable.
		 * We use it to test SPI register access.
		*/
		AD5940_WriteReg(REG_AFE_CALDATLOCK, data);

    unsigned long temp;
    uint32_t chipID;
		temp = AD5940_ReadReg(REG_AFE_CALDATLOCK);
    chipID=AD5940_GetChipID();
		if(temp != data)
		    printf("Write register test failed @0x%08lx\n", data);
		if(!(count%1000))
		    {
          printf("Read has been done %ld times, ChipID is %x\n",count, chipID);
          printf("Read/Write has been done %ld times, latest data is 0x%08lx\n", count, data);
        }
}
