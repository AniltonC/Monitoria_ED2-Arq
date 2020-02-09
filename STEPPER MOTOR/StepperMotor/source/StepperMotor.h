/*!
 * @copyright   � 2020 UFAM - Universidade Federal do Amazonas.
 *
 * @brief Stepper Motor header file for FRDM-KL25Z - Version 1.0
 * The sequence of control signals for 4 control wire is as follows:
 * 
 * Step   C0 C1 C2 C3
 *    1    1  0  0  0
 *    2    1  1  0  0
 *    3    0  1  0  0
 *    4    0  1  1  0
 *    5    0  0  1  0
 *    6    0  0  1  1
 *    7    0  0  0  1
 *    8    1  0  0  1
 *
 * @file        StepperMotor.h
 * @version     1.0
 * @date        5 Fevereiro 2020
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     MCUXpresso
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (5 Fevereiro 2020): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Anilton Carlos <aniltoncarlos9@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL)
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include <MKL25Z.h>
#include <mkl_GPIOPort.h>

typedef enum {
    halfStep = 0,
    simpleStep = 1,
    doubleStep = 2
} stepMode;

typedef enum {
    clock_wise = 0,
    counter_clock_wise = 1
} stepDirection;

// library interface descripition
class StepperMotor {
 public:
    // Construtor da classe do Motor de Passo, cujas são os gpio_Pin, de 1 a 4:
    StepperMotor(gpio_Pin coilPin_1, gpio_Pin coilPin_2,
                 gpio_Pin coilPin_3, gpio_Pin coilPin_4);

    // Habilita e Desabilita a rotação do eixo do motor
    void enableRotation();
    void disableRotation();

    /*
     *Método de configuração da rotação do Motor
     *(simpleStep, doubleStep, halfStep)
     */
    void setStepMode(stepMode mode);

    // Método de configuração do sentido de rotação
    void setDirectionOfRotation(stepDirection directionOfRotation);

    // Método que energiza as bobinas que estiverem acionadas
    void turnOnPowerCoil();

    // Método que desernegiza todas as bobinas
    void turnOffPowerCoil();

    // Método para realização dos passos
    void doStep();

 private:
    void writeCoils(int value);

    // Estado de habilitação da Rotação
    bool enableStep;

    // Modo de rotação
    stepMode mode;

    // Direção da rotação do motor
    stepDirection direction;

    // Estado da energia das bobinas
    bool powerCoil;

    // GPIO Port das bobinas do motor
    mkl_GPIOPort coil_1;
    mkl_GPIOPort coil_2;
    mkl_GPIOPort coil_3;
    mkl_GPIOPort coil_4;

    /*
     * Sequencia de Passos:
     * Se o passo for simples, serão ativadas as posições 0, 2, 4, 6
     * Se o passo for duplo, serão ativadas as posições 1, 3, 5, 7
     * Se o passo for meio, todas as posições serão ativadas sequencialmente
     */
    int allSteps[8] = {8, 12, 4, 6, 2, 3, 1, 9};

    // Posição do vetor de passos
    int currentStep, nextStep;
};

#endif /* STEPPERMOTOR_H_ */
