/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : BitIO_AD_START0.c
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-03-17, 16:28, # CodeGen: 197
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : BitIO_AD_START0
**          Pin for I/O                                    : ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/TPM2_CH0
**          Pin signal                                     : AD_START
**          Direction                                      : Output
**          Initialization                                 :
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : no
**          Safe mode                                      : no
**     Contents    :
**         Init   - LDD_TDeviceData* BitIO_AD_START0_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool BitIO_AD_START0_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         PutVal - void BitIO_AD_START0_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val);
**         ClrVal - void BitIO_AD_START0_ClrVal(LDD_TDeviceData *DeviceDataPtr);
**         SetVal - void BitIO_AD_START0_SetVal(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file BitIO_AD_START0.c
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/
/*!
**  @addtogroup BitIO_AD_START0_module BitIO_AD_START0 module documentation
**  @{
*/

/* MODULE BitIO_AD_START0. */

/* {Default RTOS Adapter} No RTOS includes */
#include "BitIO_AD_START0.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  BitIO_AD_START0_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* BitIO_AD_START0_Init(LDD_TUserData *UserDataPtr)
{
  /* Configure pin as output */
  /* GPIOB_PDDR: PDD|=4 */
  GPIOB_PDDR |= GPIO_PDDR_PDD(0x04);
  /* Set initialization value */
  /* GPIOB_PDOR: PDO&=~4 */
  GPIOB_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x04));
  /* Initialization of Port Control register */
  /* PORTB_PCR2: ISF=0,MUX=1 */
  PORTB_PCR2 = (uint32_t)((PORTB_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  return ERR_OK;
}
/*
** ===================================================================
**     Method      :  BitIO_AD_START0_GetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Returns the input/output value. If the direction is [input]
**         then the input value of the pin is read and returned. If the
**         direction is [output] then the last written value is read
**         and returned (see <Safe mode> property for limitations).
**         This method cannot be disabled if direction is [input].
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Input or output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
bool BitIO_AD_START0_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t PortData;                   /* Port data masked according to the bit used */

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PortData = GPIO_PDD_GetPortDataOutput(BitIO_AD_START0_MODULE_BASE_ADDRESS) & BitIO_AD_START0_PORT_MASK;
  return (PortData != 0U) ? (bool)TRUE : (bool)FALSE;
}

/*
** ===================================================================
**     Method      :  BitIO_AD_START0_PutVal (component BitIO_LDD)
*/
/*!
**     @brief
**         The specified output value is set. If the direction is <b>
**         input</b>, the component saves the value to a memory or a
**         register and this value will be written to the pin after
**         switching to the output mode (using <tt>SetDir(TRUE)</tt>;
**         see <a href="BitIOProperties.html#SafeMode">Safe mode</a>
**         property for limitations). If the direction is <b>output</b>,
**         it writes the value to the pin. (Method is available only if
**         the direction = <u><tt>output</tt></u> or <u><tt>
**         input/output</tt></u>).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Val             - Output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
void BitIO_AD_START0_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (Val) {
    GPIO_PDD_SetPortDataOutputMask(BitIO_AD_START0_MODULE_BASE_ADDRESS, BitIO_AD_START0_PORT_MASK);
  } else { /* !Val */
    GPIO_PDD_ClearPortDataOutputMask(BitIO_AD_START0_MODULE_BASE_ADDRESS, BitIO_AD_START0_PORT_MASK);
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  BitIO_AD_START0_ClrVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Clears (set to zero) the output value. It is equivalent to
**         the [PutVal(FALSE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void BitIO_AD_START0_ClrVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_ClearPortDataOutputMask(BitIO_AD_START0_MODULE_BASE_ADDRESS, BitIO_AD_START0_PORT_MASK);
}

/*
** ===================================================================
**     Method      :  BitIO_AD_START0_SetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the output value. It is equivalent to the
**         [PutVal(TRUE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void BitIO_AD_START0_SetVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_SetPortDataOutputMask(BitIO_AD_START0_MODULE_BASE_ADDRESS, BitIO_AD_START0_PORT_MASK);
}

/* END BitIO_AD_START0. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
