/*!
 * @copyright   � 2019 Victoria da Silva Leite <victoria.vl73@gmail.com>
 *
 * @brief       Exemplo de uso do systick da MKL25Z.
 *
 * @file        main.cpp
 * @version     1.0
 * @date        31 Janeiro 2019
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   Systick - System Tick Timer.
 *              +compiler     Kinetis� Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Vers�o (data): Descri��o breve.
 *                             ++ 1.0 (31 Janeiro 2019): Vers�o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computa��o / Engenharia El�trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Vers�o inicial:
 *                             ++ Victoria da Silva Leite <victoria.vl73@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa � um software livre; Voc� pode redistribu�-lo
 *              e/ou modific�-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              vers�o 3 da licen�a, ou qualquer vers�o posterior.
 *
 *              Este programa � distribu�do na esperan�a de que seja �til,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia impl�cita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROP�SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include <MKL25Z4.H>
#include "mkl_GPIOPort.h"
#include "mkl_SystickPeriodicInterrupt.h"

/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort blueLed(gpio_PTD1);

/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort redLed(gpio_PTB18);

/*!
 * 	Declara��o do objeto systick e configura��o para acontecer uma interrup��o a cada 100ms
 * 	e usar o clock da placa de 42MHz
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */
bool bit = 0;

void wait(int value) {
	int i = 0;
	while (i < value) {
		i++;
	}
}


/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */
extern "C" {
    void SysTick_Handler(void) {
        // LED TOGGLE
        bit = !bit;
        blueLed.writeBit(bit);
        redLed.writeBit(!bit);
    }
}

/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */
int main(void) {
    blueLed.setPortMode(gpio_output);
    redLed.setPortMode(gpio_output);

    while (1) {
        /* Espera aqui por uma interrupcao */

    }
}
