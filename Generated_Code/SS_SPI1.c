/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SS_SPI1.c
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : SPISlave_LDD
**     Version     : Component 01.047, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-03-17, 13:36, # CodeGen: 187
**     Abstract    :
**         This component "SPISlave_LDD" implements SLAVE part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : SS_SPI1
**          Device                                         : SPI1
**          Interrupt service/event                        : Disabled
**          Settings                                       :
**            Input pin                                    : Enabled
**              Pin                                        : ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/UART0_RX/SPI1_MISO
**              Pin signal                                 : SPI1_IN
**            Output pin                                   : Enabled
**              Pin                                        : PTD7/SPI1_MISO/UART0_TX/SPI1_MOSI
**              Pin signal                                 : SPI1_OUT
**            Clock pin                                    :
**              Pin                                        : ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5
**              Pin signal                                 : SPI1_SCK
**            Slave select                                 :
**              Pin                                        : PTD4/LLWU_P14/SPI1_PCS0/UART2_RX/TPM0_CH4
**              Pin signal                                 : SPI1_CS
**              Active level                               : Low
**            Attribute set                                :
**              Width                                      : 8 bits
**              MSB first                                  : yes
**              Clock polarity                             : Low
**              Clock phase                                : Change on leading edge
**              Parity                                     : None
**            HW input buffer size                         : 1
**            HW input watermark                           : 1
**            Receiver DMA                                 : Disabled
**            HW output buffer size                        : 1
**            HW output watermark                          : 1
**            Transmitter DMA                              : Disabled
**          Initialization                                 :
**            Enabled in init. code                        : no
**            Auto initialization                          : no
**            Event mask                                   :
**              OnBlockSent                                : Disabled
**              OnBlockReceived                            : Disabled
**              OnError                                    : Disabled
**     Contents    :
**         Init    - LDD_TDeviceData* SS_SPI1_Init(LDD_TUserData *UserDataPtr);
**         Enable  - LDD_TError SS_SPI1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable - LDD_TError SS_SPI1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         Main    - void SS_SPI1_Main(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file SS_SPI1.c
** @version 01.02
** @brief
**         This component "SPISlave_LDD" implements SLAVE part of synchronous
**         serial master-slave communication.
*/
/*!
**  @addtogroup SS_SPI1_module SS_SPI1 module documentation
**  @{
*/

/* MODULE SS_SPI1. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */

#include "SS_SPI1.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif

#define AVAILABLE_EVENTS_MASK 0x00U

/* These constants contain pins masks */
#define SS_SPI1_AVAILABLE_PIN_MASK (LDD_SPISLAVE_INPUT_PIN | LDD_SPISLAVE_OUTPUT_PIN | LDD_SPISLAVE_CLK_PIN | LDD_SPISLAVE_SS_PIN)

typedef struct {
  bool EnUser;                         /* Enable/Disable device */
  LDD_SPISLAVE_TError ErrFlag;         /* Error flags */
  LDD_TUserData *UserData;             /* User device data structure */
} SS_SPI1_TDeviceData;                 /* Device data structure type */

typedef SS_SPI1_TDeviceData* SS_SPI1_TDeviceDataPtr; /* Pointer to the device data structure */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static SS_SPI1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* Internal method prototypes */
static void HWEnDi(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  SS_SPI1_Init (component SPISlave_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated.
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* SS_SPI1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  SS_SPI1_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->EnUser = FALSE;       /* Disable device */
  DeviceDataPrv->ErrFlag = 0x00U;      /* Clear error flags */
  /* SIM_SCGC4: SPI1=1 */
  SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
  /* SPI1_C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
  SPI1_C1 = SPI_C1_CPHA_MASK;          /* Clear control register */
  /* PORTD_PCR6: ISF=0,MUX=2 */
  PORTD_PCR6 = (uint32_t)((PORTD_PCR6 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTD_PCR7: ISF=0,MUX=2 */
  PORTD_PCR7 = (uint32_t)((PORTD_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTD_PCR5: ISF=0,MUX=2 */
  PORTD_PCR5 = (uint32_t)((PORTD_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTD_PCR4: ISF=0,MUX=2,PE=1 */
  PORTD_PCR4 = (uint32_t)((PORTD_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_PE_MASK
               );
  /* SPI1_C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
  SPI1_C1 = SPI_C1_CPHA_MASK;          /* Set Configuration register */
  /* SPI1_C2: SPMIE=0,??=0,TXDMAE=0,MODFEN=0,BIDIROE=0,RXDMAE=0,SPISWAI=0,SPC0=0 */
  SPI1_C2 = 0x00U;                     /* Set Configuration register */
  /* SPI1_BR: ??=0,SPPR=0,SPR=0 */
  SPI1_BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00)); /* Set baud rate register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_SS_SPI1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  SS_SPI1_Enable (component SPISlave_LDD)
*/
/*!
**     @brief
**         This method enables SPI device. This method is intended to
**         be used together with <Disable()> method to temporary switch
**         On/Off the device after the device is initialized. This
**         method is required if the <Enabled in init. code> property
**         is set to "no" value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
*/
/* ===================================================================*/
LDD_TError SS_SPI1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  if (!((SS_SPI1_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    ((SS_SPI1_TDeviceDataPtr)DeviceDataPtr)->EnUser = TRUE; /* If yes then set the flag "device enabled" */
    HWEnDi((SS_SPI1_TDeviceDataPtr)DeviceDataPtr); /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SS_SPI1_Disable (component SPISlave_LDD)
*/
/*!
**     @brief
**         Disables the SPI device. When the device is disabled, some
**         component methods should not be called. If so, error
**         ERR_DISABLED may be reported. This method is intended to be
**         used together with <Enable()> method to temporary switch
**         on/off the device after the device is initialized. This
**         method is not required. The <Deinit()> method can be used to
**         switch off and uninstall the device.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
*/
/* ===================================================================*/
LDD_TError SS_SPI1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  if (((SS_SPI1_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device enabled by user? */
    ((SS_SPI1_TDeviceDataPtr)DeviceDataPtr)->EnUser = FALSE; /* If yes then set the flag "device disabled" */
    HWEnDi((SS_SPI1_TDeviceDataPtr)DeviceDataPtr); /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SS_SPI1_Main (component SPISlave_LDD)
*/
/*!
**     @brief
**         This method is available only in the polling mode (Interrupt
**         service/event = 'no'). If interrupt service is disabled this
**         method replaces the interrupt handler. This method should be
**         called if Receive/SendBlock was invoked before in order to
**         run the reception/transmission. The end of the
**         receiving/transmitting is indicated by OnBlockSent or
**         OnBlockReceived event.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void SS_SPI1_Main(LDD_TDeviceData *DeviceDataPtr)
{
  SS_SPI1_TDeviceDataPtr DeviceDataPrv = (SS_SPI1_TDeviceDataPtr)DeviceDataPtr;
  uint8_t StatReg = SPI_PDD_ReadStatusReg(SPI1_BASE_PTR); /* Read status register */

  (void)DeviceDataPrv;                 /* Supress unused variable warning if needed */
  if ((StatReg & SPI_PDD_RX_BUFFER_FULL) != 0U) { /* Is any char in HW Rx buffer? */
  }
}

/*
** ===================================================================
**     Method      :  HWEnDi (component SPISlave_LDD)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the
**         component. The method is called automatically as a part of the
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(LDD_TDeviceData *DeviceDataPtr)
{
  SS_SPI1_TDeviceData* DeviceDataPrv = (SS_SPI1_TDeviceData*)DeviceDataPtr;

  if (DeviceDataPrv->EnUser) {         /* Enable device? */
    SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_ENABLE); /* Enable device */
  } else {
    SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_DISABLE); /* Disable device */
  }
}

/*lint -restore Enable MISRA rule (11.4) checking. */
/* END SS_SPI1. */

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
