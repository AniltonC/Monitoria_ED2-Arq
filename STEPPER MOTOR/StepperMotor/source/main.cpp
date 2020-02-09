/**
* @file main.cpp
*
* @copyright 2020 UFAM - Universidade Federal do Amazonas
*
* @brief Stepper Motor example file for FRDM-KL25Z - Version 1.0
*
* @author aniltoncarlos9@gmail.com (Anilton Carlos).
*
* @project Monitoria Arquitetura de Sistemas Digitais 2020
*
**/

#include <MKL25Z4.H>
#include <StepperMotor.h>
#include <mkl_GPIOPort.h>
#include <mkl_SystickPeriodicInterrupt.h>

// Chamada do contrutor da classe StepperMotor
StepperMotor MotorPassos(gpio_PTD2, gpio_PTD0, gpio_PTD5, gpio_PTA13);

/*
 * Led RGB da placa para auxiliar
 * no discernimento dos Modos de Passo
 */
mkl_GPIOPort greenSimpleLed(gpio_PTB19);
mkl_GPIOPort blueDoubleLed(gpio_PTD1);
mkl_GPIOPort redHalfLed(gpio_PTB18);

// Systick com interrupção a cada 1 ms
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(1, clock42Mhz);

uint64_t directionMotorCounter = 0;

extern "C"
{
  void SysTick_Handler(void)
  {
    // Execução dos passos a cada interrupção
    MotorPassos.doStep();
    directionMotorCounter++;
  }
}

void setup() {
  greenSimpleLed.setPortMode(gpio_output);
  blueDoubleLed.setPortMode(gpio_output);
  redHalfLed.setPortMode(gpio_output);

  MotorPassos.setStepMode(simpleStep);
  MotorPassos.turnOnPowerCoil();
  MotorPassos.setDirectionOfRotation(clock_wise);
  MotorPassos.enableRotation();

  greenSimpleLed.writeBit(0);
  blueDoubleLed.writeBit(1);
  redHalfLed.writeBit(1);
}

int main(void)
{
  setup();
  uint8_t multiplicador = 1;
  stepMode selectStepMode = simpleStep;

  while (true)
  {
    // Alterna a direção sempre que completar 1 volta
    if (directionMotorCounter == (2048.000 * multiplicador)) {
      MotorPassos.setDirectionOfRotation(counter_clock_wise);
    } else if (directionMotorCounter == (4096.000 * multiplicador)) {
      MotorPassos.setDirectionOfRotation(clock_wise);
      directionMotorCounter = 0;
      /* Sempre que completa a segunda volta,
       * troca o modo de passo
       * Passo Simples - LED VERDE
       * Passo Duplo - LED AZUL
       * Passo Meio - LED VERMELHO
       */
      if (selectStepMode == simpleStep)  {
        selectStepMode = doubleStep;
        multiplicador = 1;
        greenSimpleLed.writeBit(1);
        blueDoubleLed.writeBit(0);
        redHalfLed.writeBit(1);
      } else if (selectStepMode == doubleStep) {
        selectStepMode = halfStep;
        multiplicador = 2;
        greenSimpleLed.writeBit(1);
        blueDoubleLed.writeBit(1);
        redHalfLed.writeBit(0);
      } else {
        selectStepMode = simpleStep;
        multiplicador = 1;
        greenSimpleLed.writeBit(0);
        blueDoubleLed.writeBit(1);
        redHalfLed.writeBit(1);
      }
      MotorPassos.setStepMode(selectStepMode);
    }
  }
}
