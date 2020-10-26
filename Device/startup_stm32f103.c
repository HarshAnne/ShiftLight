/*
 * startup_stm32f103.c
 * Author: Harsh Anne
 */ 

#include "stm32f1xx.h"

#define __stack_size 0x200

extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

extern void _estack;

// __align(8) unsigned char __stack[__stack_size] __attribute__((section("STACK"), zero_init));

// prototypes for exception & interrupt handlers
void __WEAK Reset_Handler(void);
void __WEAK NMI_Handler(void);
void __WEAK HardFault_Handler(void);
void __WEAK MemManage_Handler(void);
void __WEAK BusFault_Handler(void);
void __WEAK UsageFault_Handler(void);
void __WEAK MemManage_Handler(void);
void __WEAK SVC_Handler(void);
void __WEAK DebugMon_Handler(void);
void __WEAK PendSV_Handler(void);
void __WEAK SysTick_Handler(void);

/* External Interrupts */
void __WEAK WWDG_IRQHandler(void);
void __WEAK PVD_IRQHandler(void);
void __WEAK TAMPER_IRQHandler(void);
void __WEAK RTC_IRQHandler(void);
void __WEAK FLASH_IRQHandler(void);
void __WEAK RCC_IRQHandler(void);
void __WEAK EXTI0_IRQHandler(void);
void __WEAK EXTI1_IRQHandler(void);
void __WEAK EXTI2_IRQHandler(void);
void __WEAK EXTI3_IRQHandler(void);
void __WEAK EXTI4_IRQHandler(void);
void __WEAK DMA1_Channel1_IRQHandler(void);
void __WEAK DMA1_Channel2_IRQHandler(void);
void __WEAK DMA1_Channel3_IRQHandler(void);
void __WEAK DMA1_Channel4_IRQHandler(void);
void __WEAK DMA1_Channel5_IRQHandler(void);
void __WEAK DMA1_Channel6_IRQHandler(void);
void __WEAK DMA1_Channel7_IRQHandler(void);
void __WEAK ADC1_2_IRQHandler(void);
void __WEAK USB_HP_CAN1_TX_IRQHandler(void);
void __WEAK USB_LP_CAN1_RX0_IRQHandler(void);
void __WEAK CAN1_RX1_IRQHandler(void);
void __WEAK CAN1_SCE_IRQHandler(void);
void __WEAK EXTI9_5_IRQHandler(void);
void __WEAK TIM1_BRK_IRQHandler(void);
void __WEAK TIM1_UP_IRQHandler(void);
void __WEAK TIM1_TRG_COM_IRQHandler(void);
void __WEAK TIM1_CC_IRQHandler(void);
void __WEAK TIM2_IRQHandler(void);
void __WEAK TIM3_IRQHandler(void);
void __WEAK TIM4_IRQHandler(void);
void __WEAK I2C1_EV_IRQHandler(void);
void __WEAK I2C1_ER_IRQHandler(void);
void __WEAK I2C2_EV_IRQHandler(void);
void __WEAK I2C2_ER_IRQHandler(void);
void __WEAK SPI1_IRQHandler(void);
void __WEAK SPI2_IRQHandler(void);
void __WEAK USART1_IRQHandler(void);
void __WEAK USART2_IRQHandler(void);
void __WEAK USART3_IRQHandler(void);
void __WEAK EXTI15_10_IRQHandler(void);
void __WEAK RTCAlarm_IRQHandler(void);
void __WEAK USBWakeUp_IRQHandler(void);

extern int main(void);
void __Init_Data(void);

void (* const__Vectors[])(void) __attribute__((section(".vector_table"))) = 
{
    &_estack, //Top of Stack
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    //External Interrupts
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMPER_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler, 
    EXTI3_IRQHandler, 
    EXTI4_IRQHandler, 
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler, 
    DMA1_Channel3_IRQHandler, 
    DMA1_Channel4_IRQHandler, 
    DMA1_Channel5_IRQHandler, 
    DMA1_Channel6_IRQHandler, 
    DMA1_Channel7_IRQHandler, 
    ADC1_2_IRQHandler, 
    USB_HP_CAN1_TX_IRQHandler,
    USB_LP_CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler, 
    TIM1_UP_IRQHandler, 
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTCAlarm_IRQHandler,
    USBWakeUp_IRQHandler,
};

void Reset_Handler(void)
{
    __Init_Data();

    main();

    while(1);
}

void __Init_Data(void)
{
    unsigned long *pulSrc, *pulDest;

    /* Copy the data segment initializers from flash to SRAM */

    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    /* Zero fill the bss segment */
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }
}

#pragma weak MMI_Handler = Default_Handler
#pragma __WEAK MemManage_Handler = Default_Handler
#pragma __WEAK BusFault_Handler = Default_Handler
#pragma __WEAK UsageFault_Handler = Default_Handler
#pragma __WEAK SVC_Handler = Default_Handler
#pragma __WEAK DebugMon_Handler = Default_Handler
#pragma __WEAK PendSV_Handler = Default_Handler
#pragma __WEAK SysTick_Handler = Default_Handler
#pragma __WEAK WWDG_IRQHandler = Default_Handler
#pragma __WEAK PVD_IRQHandler = Default_Handler
#pragma __WEAK TAMPER_IRQHandler = Default_Handler
#pragma __WEAK RTC_IRQHandler = Default_Handler
#pragma __WEAK FLASH_IRQHandler = Default_Handler
#pragma __WEAK RCC_IRQHandler = Default_Handler
#pragma __WEAK EXTI0_IRQHandler = Default_Handler
#pragma __WEAK EXTI1_IRQHandler = Default_Handler
#pragma __WEAK EXTI2_IRQHandler = Default_Handler
#pragma __WEAK EXTI3_IRQHandler = Default_Handler
#pragma __WEAK EXTI4_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel1_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel2_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel3_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel4_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel5_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel6_IRQHandler = Default_Handler
#pragma __WEAK DMA1_Channel7_IRQHandler = Default_Handler
#pragma __WEAK ADC1_2_IRQHandler = Default_Handler
#pragma __WEAK USB_HP_CAN1_TX_IRQHandler = Default_Handler
#pragma __WEAK USB_LP_CAN1_RX0_IRQHandler = Default_Handler
#pragma __WEAK CAN1_RX1_IRQHandler = Default_Handler
#pragma __WEAK CAN1_SCE_IRQHandler = Default_Handler
#pragma __WEAK EXTI9_5_IRQHandler = Default_Handler
#pragma __WEAK TIM1_BRK_IRQHandler = Default_Handler
#pragma __WEAK TIM1_UP_IRQHandler = Default_Handler
#pragma __WEAK TIM1_TRG_COM_IRQHandler = Default_Handler
#pragma __WEAK TIM1_CC_IRQHandler = Default_Handler
#pragma __WEAK TIM2_IRQHandler = Default_Handler
#pragma __WEAK TIM3_IRQHandler = Default_Handler
#pragma __WEAK TIM4_IRQHandler = Default_Handler
#pragma __WEAK I2C1_EV_IRQHandler = Default_Handler
#pragma __WEAK I2C1_ER_IRQHandler = Default_Handler
#pragma __WEAK I2C2_EV_IRQHandler = Default_Handler
#pragma __WEAK I2C2_ER_IRQHandler = Default_Handler
#pragma __WEAK SPI1_IRQHandler = Default_Handler
#pragma __WEAK SPI2_IRQHandler = Default_Handler
#pragma __WEAK USART1_IRQHandler = Default_Handler
#pragma __WEAK USART2_IRQHandler = Default_Handler
#pragma __WEAK USART3_IRQHandler = Default_Handler
#pragma __WEAK EXTI15_10_IRQHandler = Default_Handler
#pragma __WEAK RTCAlarm_IRQHandler = Default_Handler
#pragma __WEAK USBWakeUp_IRQHandler = Default_Handler

void Default_Handler(void) 
{
  /* Go into an infinite loop. */
  while (1) 
  {
  }
}