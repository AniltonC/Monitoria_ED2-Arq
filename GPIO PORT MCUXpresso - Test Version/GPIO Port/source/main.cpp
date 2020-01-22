/*!
 * @copyright   2019 UFAM - Universidade Federal do Amazonas.
 * 
 * @brief       Exemplo de uso do GPIO da MKL25Z no software MCUXpresso.
 * 
 * @example     main.cpp
 * @version     1.0
 * @date        15 Janeiro 2019
 * 
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Anilton Carlos  <aclr@icomp.ufam.edu.br>
 */

#include "mkl_GPIOPort.h"

/*!
 * Inicialização dos dispositivos
 */
mkl_GPIOPort blueLed(gpio_PTD1);
mkl_GPIOPort redLed(gpio_PTB18);
mkl_GPIOPort greenLed(gpio_PTB19);

mkl_GPIOPort pushButton(gpio_PTA2);

/*!
 *   @fn         setup
 *
 *   @brief      Realiza a configuração do periférico para a entrada e saída.
 *
 *   Este procedimento realiza a configuração do pino PTA2 do GPIO para o modo
 *   entrada e a configuração dos pinos PTD1, PTB18, PTB19 para o modo saída (RGB)
 *
 *   @details    O led RGB é do tipo anodo comum.
 */

void setup()
{
	/*!
	 * Configura o pino para o modo saída.
	 */
	blueLed.setPortMode(gpio_output);
	redLed.setPortMode(gpio_output);
	greenLed.setPortMode(gpio_output);
  	/*!
  	 * Configura o pino para o modo entrada com resistor de pull up.
 	 */
	pushButton.setPortMode(gpio_input);
	pushButton.setPullResistor(gpio_pullUpResistor);
}

/*!
 *   @fn     main
 *
 *   @brief    Acende o Led RGB conforme a situação de uma chave.
 *
 *   Este programa realiza o teste da classe do periférico GPIO, onde
 *   quatro portas são configuradas, três de saída para o Led RGB, e
 *	 uma de entrada para um botão. Se o botão
 *	 for pressionado, o Led RGB acenderá alternando entre as suas cores
 *	 padrão.
 *
 *   @details  A porta configurada como entrada possui um resistor de pull-up
 *             interno, sendo necessário a ligação da chave ao terra.
 *
 *   @return  sempre retorna o valor 0.
 */
int main()
{
	uint32_t contador = 0;
	uint8_t select = 0;
	setup();

	while (true)
	{
		/*!
	 	 * Leitura do botão.
		 */
		if (pushButton.readBit() == 1)
		{
			/*!
	 		 * Contagem para alternar entre as cores do Led RGB.
			 */
			contador++;
			if (contador >= 50000)
			{
				select++;
				if (select == 3)
				{
					select = 0;
				}

				contador = 0;
			}

			/*!
	 		 * Alteração dos valores das portas do Led RGB de acordo com a cor selecionada,
			 * 1 - OFF,
			 * 0 - ON.
			 */
			if (select == 0)
			{
				redLed.writeBit(0);
				blueLed.writeBit(1);
				greenLed.writeBit(1);
			}
			else if (select == 1)
			{
				redLed.writeBit(1);
				blueLed.writeBit(1);
				greenLed.writeBit(0);
			}
			else if (select == 2)
			{
				redLed.writeBit(1);
				blueLed.writeBit(0);
				greenLed.writeBit(1);
			}
		}
		else
		{
			redLed.writeBit(1);
			blueLed.writeBit(1);
			greenLed.writeBit(1);
		}
	}

	return 0;
}
