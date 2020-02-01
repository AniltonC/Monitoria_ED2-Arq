/*
 * StepperMotor.h  - Stepper Motor library for FRDM-KL25Z - Version 1.0
 *
 * Author: Anilton Carlos - aniltoncarlos9@gmail.com / aclr@icomp.ufam.edu.br
 * 
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
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include "MKL25Z.h"
#include "mkl_GPIOPort.h"

typedef enum
{
    halfStep = 0,
    simpleStep = 1,
    doubleStep = 2
} stepMode;

typedef enum
{
    clock_wise = 0,
    counter_clock_wise = 1
} stepDirection;

// library interface descripition
class StepperMotor
{
public:
    // constructor:
    StepperMotor(gpio_Pin coilPin_1, gpio_Pin coilPin_2,
                 gpio_Pin coilPin_3, gpio_Pin coilPin_4);

    // Habilita e Desabilita a rotação do eixo do motor
    void enableRotation();
    void disableRotation();

    // Método de configuração da rotação do Motor (SimpleStep, DoubleSteps, HalfStep)
    void setStepMode(stepMode mode);

    // Método de configuração do sentido de rotação
    void setDirectionOfRotation(stepDirection directionOfRotation);

    // Métodos de configuração da energia das bobinas
    void turnOnPowerCoil();
    void turnOffPowerCoil();

    // Método para realização dos passos
    void doStep();

private:
    void writeCoils(int value);

    bool enableStep;         // Estado de habilitação da Rotação
    stepMode mode;           // Modo de rotação                 
    stepDirection direction; // Direção da rotação do motor     
    bool powerCoil;          // Estado da energia das bobinas   

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

    int currentStep, nextStep; // Posição do vetor de passos
};

#endif /* STEPPERMOTOR_H_ */
