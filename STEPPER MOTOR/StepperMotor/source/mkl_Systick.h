/*!
 * @copyright   � 2019 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para  o System Tick Timer (MKL25Z).
 *
 * @file        mkl_Systick.h
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


#ifndef MKL_SYSTICK_H_
#define MKL_SYSTICK_H_

#include <MKL25Z.h>
#include <stdint.h>

/* !
 *	Defini��o dos poss�veis valores de clock
 */
typedef enum {
    clock2Mhz = 0 ,  //!< System clock system divided by 16
    clock42Mhz = 1   //!< System clock
} systick_clockSource;


/*!
 *  @class    mkl_Systick
 *
 *  @brief    A classe mkl_Systick representa o perif�rico System Tick Timer da MKL25Z.
 *
 *  @details  Esta classe � usada para a gera��o temporiza��es.
 *
 *  @section  EXAMPLES USAGE
 *
 *   Uso dos m�todos para o uso do Systick
 *     +fn setClockSource(systick_clockSource clock);
 *     +fn setReload(uint32_t reloadValue);
 *     +fn enableCounter();
 *     +fn disableCounter();
 *     +fn clearCounter();
 *     +fn enableInterrupt();
 *     +fn disableInterrupt();
 *     +fn setRegister();
 */
class mkl_Systick {
 public:
	/*!
	 * M�todos de configura��o do systick
	 */
    void setClockSource(systick_clockSource clock);
    void setReload(uint32_t reloadValue);
    void enableCounter();
    void disableCounter();
    void clearCounter();
	/*!
	 * M�todos que configuram a interrup��o
	 */
    void enableInterrupt();
    void disableInterrupt();

 private:
	/*!
     * M�todo interno para endere�ar os registradores
	 */
    void setRegister();

	/*!
	 *  Endere�o no mapa de mem�ria do Control and Status Register
	 */
    volatile unsigned int *addrSTCSR;

	/*!
	 *  Endere�o no mapa de mem�ria do Reload Value Register
	 */
    volatile unsigned int *addrSTRVR;

	/*!
	 *  Endere�o no mapa de mem�ria do Current Value Register
     */
    volatile unsigned int *addrSTCVR;

	/*!
	 *  Endere�o no mapa de mem�ria do Calibration Value Register
	 */
    volatile unsigned int *addrSTCALIB;
};

#endif  // MKL_SYSTICK_H_
