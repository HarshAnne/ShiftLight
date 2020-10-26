#include "stm32f10x.h"

int main(void)
{
    /* Enable IO Port C clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* Configure GPIOC for PC13 */
    /*  CNF13[1:0]  = 0b00;
        MODE13[1:0] = 0b01;
        GPIOC->CRH = 0x00100000;
    */

    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    
    GPIOC->BSRR = (1 << 13);

    while(1)
    {
        volatile int i;
        for(i = 0;i < 500000; i++)
        {
        }
        GPIOC->ODR ^= (1 << 13);
    }
    return 0;
}