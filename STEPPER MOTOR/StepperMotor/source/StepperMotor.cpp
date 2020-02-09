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
 * @file        StepperMotor.cpp
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

#include "StepperMotor.h"

StepperMotor::StepperMotor(gpio_Pin coilPin_1, gpio_Pin coilPin_2,
                           gpio_Pin coilPin_3, gpio_Pin coilPin_4) :
                           coil_1(coilPin_1), coil_2(coilPin_2),
                           coil_3(coilPin_3), coil_4(coilPin_4) {
    // Setup dos pinos na KL25Z
    this->coil_1.setPortMode(gpio_output);
    this->coil_2.setPortMode(gpio_output);
    this->coil_3.setPortMode(gpio_output);
    this->coil_4.setPortMode(gpio_output);

    // Estado de habilitação da Rotação
    this->enableStep = false;
    // Modo de rotação
    this->mode = simpleStep;
    // Direção da rotação do motor
    this->direction = clock_wise;
    // Estado da energia das bobinas
    this->powerCoil = false;
    // Posição do vetor de passos
    this->currentStep = 0;
    // Posição futura do vetor de passos
    this->nextStep = 0;

    this->turnOffPowerCoil();
}

void StepperMotor::enableRotation() {
    this->enableStep = true;
}

void StepperMotor::disableRotation() {
    this->enableStep = false;
}

void StepperMotor::setStepMode(stepMode mode) {
    this->mode = mode;
}

void StepperMotor::setDirectionOfRotation(stepDirection directionOfRotation) {
    this->direction = directionOfRotation;
}

void StepperMotor::turnOffPowerCoil() {
    this->powerCoil = false;
}

void StepperMotor::turnOnPowerCoil() {
    this->powerCoil = true;
}

void StepperMotor::writeCoils(int value) {
    switch (value) {
    case 0:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(false);
        break;

    case 1:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(true);
        break;

    case 2:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(true);
        this->coil_4.writeBit(false);
        break;

    case 3:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(true);
        this->coil_4.writeBit(true);
        break;

    case 4:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(true);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(false);
        break;

    case 6:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(true);
        this->coil_3.writeBit(true);
        this->coil_4.writeBit(false);
        break;

    case 8:
        this->coil_1.writeBit(true);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(false);
        break;

    case 9:
        this->coil_1.writeBit(true);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(true);
        break;

    case 12:
        this->coil_1.writeBit(true);
        this->coil_2.writeBit(true);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(false);
        break;

    default:
        this->coil_1.writeBit(false);
        this->coil_2.writeBit(false);
        this->coil_3.writeBit(false);
        this->coil_4.writeBit(false);
        break;
    }
}

void StepperMotor::doStep() {
    if (enableStep == true && powerCoil == true) {
        currentStep = nextStep;
        /*
         * Movimentação do Motor em Passo Simples
         * posições 0, 2, 4 e 6 do vetor allSteps
         */ 
        if (mode == simpleStep) {
            // Verifica se a posição do vetor é adequada para o passo simples
            if ((currentStep % 2) != 0) {
                if (direction == clock_wise) {
                    if (currentStep == 7) {
                        currentStep = 0;
                    } else {
                        currentStep++;
                    }
                } else {
                    currentStep--;
                }
            }

            // Realização do Passo
            writeCoils(allSteps[currentStep]);

            // Proximo Passo
            if (direction == clock_wise) {
                if (currentStep == 6) {
                    nextStep = 0;
                } else {
                    nextStep = currentStep + 2;
                }
            } else {
                if (currentStep == 0) {
                    nextStep = 6;
                } else {
                    nextStep = currentStep - 2;
                }
            }
        } else if (mode == doubleStep) {
        /* 
         * Movimentação do Motor em Passos Duplos
         * posições 1, 3, 5 e 7 do vetor allSteps
         */
            // Verifica se a posição do vetor é adequada para o passo simples
            if ((currentStep % 2) == 0) {
                if (direction == clock_wise) {
                    currentStep++;
                } else {
                    if (currentStep == 0) {
                        currentStep = 7;
                    } else {
                        currentStep--;
                    }
                }
            }

            // Realização do Passo
            writeCoils(allSteps[currentStep]);

            // Proximo Passo
            if (direction == clock_wise) {
                if (currentStep == 7) {
                    nextStep = 1;
                } else {
                    nextStep = currentStep + 2;
                }
            } else {
                if (currentStep == 1) {
                    nextStep = 7;
                } else {
                    nextStep = currentStep - 2;
                }
            }
        } else {
        /* Movimentação do Motor em Meio Passo
         * todas as posições do vetor allSteps
         */
          // Realização do Passo
            writeCoils(allSteps[currentStep]);

            // Proximo Passo
            if (direction == clock_wise) {
                if (currentStep == 7) {
                    nextStep = 0;
                } else {
                    nextStep = currentStep + 1;
                }
            } else {
                if (currentStep == 0) {
                    nextStep = 7;
                } else {
                    nextStep = currentStep - 1;
                }
            }
        }
    } else if (powerCoil == false) {
        // Todas as bobinas receberão valor lógico 0
        writeCoils(0);
    }
}
