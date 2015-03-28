/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config =
{
  {VAL_GPIOAODR, VAL_GPIOACRL, VAL_GPIOACRH},
  {VAL_GPIOBODR, VAL_GPIOBCRL, VAL_GPIOBCRH},
  {VAL_GPIOCODR, VAL_GPIOCCRL, VAL_GPIOCCRH},
  {VAL_GPIODODR, VAL_GPIODCRL, VAL_GPIODCRH},
  {VAL_GPIOEODR, VAL_GPIOECRL, VAL_GPIOECRH},
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  stm32_clock_init();
}

#if HAL_USE_MMC_SPI
/* Board-related functions related to the MMC_SPI driver.*/
bool_t mmc_lld_is_card_inserted(MMCDriver *mmcp) {

  (void)mmcp;
  return palReadPad(GPIOC, GPIOC_MMCCP);
}

bool_t mmc_lld_is_write_protected(MMCDriver *mmcp) {

  (void)mmcp;
  return !palReadPad(GPIOC, GPIOC_MMCWP);
}
#endif

	/* Maximum speed SPI configuration (18MHz, CPHA=0, CPOL=0, MSb first).*/
//SPI_CR1_BR_0 - 18 mhz, BT_1=9Mhz
static SPIConfig hs_spicfg = {NULL, IOPORT2, GPIOB_SPI2NSS, SPI_CR1_BR_1};

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
		 /*
   * SPI1 I/O pins setup.
   */
  palSetPadMode(IOPORT2, 13, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* SCK. */
  palSetPadMode(IOPORT2, 14, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MISO.*/
  palSetPadMode(IOPORT2, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* MOSI.*/
  palSetPadMode(IOPORT2, GPIOB_SPI2NSS, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(IOPORT2, GPIOB_SPI2NSS);
	
	spiStart(&SPID2, &hs_spicfg);       /* Setup transfer parameters.       */
  //  spiAcquireBus(&SPID2);              /* Acquire ownership of the bus.    */
  //    palClearPad(IOPORT3, GPIOC_LED);    /* LED ON.                          */
}
