/*
 * main.c
 * Author: Harsh Anne
 */

/* == Headers ============================================================= */

#include "stm32f1xx.h"
#include "Types.h"


/* == Macros ============================================================== */


/* == Types =============================================================== */

typedef _Bool boolean;

/* == Variables =========================================================== */

static volatile uint32_t Main_SysTickTimeMs;
static volatile boolean Main_SysTickTimeFlag;


/* == Prototypes ========================================================== */

static inline void Main_SysTickInit(void);
static inline void Main_SysTickHandler(void);
static inline void Main_SysClockInit(void);


/* == Functions =========================================================== */

int 
main(void)
{
    /* disable all interrupts */
    __disable_irq();

    /*Setup system clock */
    Main_SysClockInit();


    /* Enable IO Port C clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* Configure GPIOC for PC13 */
    /*  CNF13[1:0]  = 0b00;
        MODE13[1:0] = 0b01;
        GPIOC->CRH = 0x00100000;
    */

    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    
    // Turn off LED
    GPIOC->BSRR = (1 << 13);

    Main_SysTickInit();

    volatile int i = 0;

    while(1)
    {
        Main_SysTickHandler();

        /* Every 1s toggle LED */
        if((0U == (Main_SysTickTimeMs % 1000)) && (Main_SysTickTimeMs > 0U) && (Main_SysTickTimeFlag == TRUE))
        {
            Main_SysTickTimeFlag = FALSE;
            i = (i == 0) ? 1 : 0;
            if(i == 0)
            {
                GPIOC->BSRR = (1 << 13);
            }
            else
            {
                GPIOC->BRR = (1 << 13);
            }
            
            // GPIOC->ODR ^= (1 << 13);
        }
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

static inline void 
Main_SysClockInit(void)
{
    /*
        This func sets up the system clock to use HSI(internal clock source),
        and sets the system clock to 48 MHz so that USB can be used.
    */

    RCC->CR |= (1 << 0);                // HSION enable internal clock
    while(!(RCC->CR & (1 << 1)));       // Wait for HSI 

    RCC->CFGR |= (0b1010 << 18);         // Set PLL multiplication to 9
    RCC->CFGR &= ~(1 << 16);            // Set PLL source to HSI

    FLASH->ACR = 0b10010;               // Enable flash prefetch

    RCC->CR |= (1 << 24);                // Enable PLL
    while(!(RCC->CR & (1 << 25)));      // Wait till PLL is ready

    RCC->CFGR = (RCC->CFGR | 0b10);// Set PLL as Clock Source

    while(!(RCC->CFGR & (1 << 3)));     // Wait till PLL is CLK src
}

/* ------------------------------------------------------------------------ */

static inline void 
Main_SysTickInit(void)
{
    /* Initialize SysTick for counter for bootloader timeout */
    /* System Clock is 48 MHz */

    // SysTick_Config(48000);
    SysTick->LOAD = (48000 - 1);
    SysTick->VAL = 0UL;
    // NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    
    Main_SysTickTimeMs = 0UL;
}

/* ------------------------------------------------------------------------ */

static inline void
Main_SysTickHandler(void)
{
    if(SysTick_CTRL_COUNTFLAG_Msk == ((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk))
    {
        SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Msk;
        Main_SysTickTimeMs++;
        Main_SysTickTimeFlag = TRUE;
    }
}
