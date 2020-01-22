#include "MKL25Z4.h"
#include "mkl_GPIOPort.h"
#include "mkl_GPIOInterrupt.h"

mkl_GPIOPort redLed(gpio_PTB18), blueLed(gpio_PTD1);
mkl_GPIOInterrupt gpioPTD0(gpio_PTD0);
volatile bool wasIntPTD0 = false;

void delayMs(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 7000; j++)
        {
        }
    }
}

extern "C"
{
    void PORTD_IRQHandler(void)
    {
        gpioPTD0.getInterruptFlag();

        if (gpioPTD0.thisGpioTriggedIntr() == true)
        {
            wasIntPTD0 = true;
        }

        gpioPTD0.clearInterruptFlag();
    }
}

int main(void)
{
    __disable_irq();

    redLed.setPortMode(gpio_output);
    blueLed.setPortMode(gpio_output);

    redLed.writeBit(true);
    blueLed.writeBit(true);

    gpioPTD0.setPortMode(gpio_input);
    gpioPTD0.setPullResistor(gpio_pullUpResistor);
    gpioPTD0.enableInterrupt(gpio_onRisingEdge);

    __enable_irq();

    while (true)
    {
        redLed.toogleBit();
        delayMs(200);

        if (wasIntPTD0 == true)
        {
            for (int i = 0; i < 6; i++)
            {
                blueLed.toogleBit();
                delayMs(200);
            }
            wasIntPTD0 = false;
        }
    }
}