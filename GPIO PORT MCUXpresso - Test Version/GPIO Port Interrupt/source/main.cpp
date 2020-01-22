#include "mkl_GPIOPort.h"
#include "mkl_GPIOInterrupt.h"

/*!
 * Inicialização dos dispositivos
 */
mkl_GPIOPort redLed(gpio_PTB18), blueLed(gpio_PTD1);
mkl_GPIOInterrupt gpioPTD0(gpio_PTD0);

/*!
 * Flag de interrupção da porta D
 */
volatile bool wasIntPTD0 = false;

/*!
 * Função delay (loop de contagem) em milissegundos
 */
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
    /*!
     *   @fn PORTD_IRQHandler
     *
     *   @brief      Rotina de serviço de interrupção de gpio.
     *
     *   @details    Trata a interrupção do gpio da PORT D.
     */
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
    // Desabilita-se as interrupções do microcontrolador para configuração das portas
    __disable_irq();
    
    // Configurando as portas dos LEDs como portas de saída e inicialmente desligados
    redLed.setPortMode(gpio_output);
    blueLed.setPortMode(gpio_output);

    redLed.writeBit(true);
    blueLed.writeBit(true);

    // Configurando a porta do botão de interrupção como porta de entrada
    gpioPTD0.setPortMode(gpio_input);
    gpioPTD0.setPullResistor(gpio_pullUpResistor);
    gpioPTD0.enableInterrupt(gpio_onRisingEdge);

    // Finalizada as configurações, reabilita-se as interrupções
    __enable_irq();

    while (true)
    {
        // Tratamento da interrupção do programa
        if (wasIntPTD0 == true)
        {
            for (int i = 0; i < 3; i++)
            {
                blueLed.writeBit(0);
                delayMs(50);
                blueLed.writeBit(1);
                delayMs(50);
            }
            wasIntPTD0 = false;
        }
        // Se não houver interrupção, rodar o programa normalmente
        else
        {
            redLed.writeBit(0);
            delayMs(50);
            redLed.writeBit(1);
            delayMs(50);
        }
    }
}