#include "MKL25Z.h"
#include "StepperMotor.h"
#include "mkl_SystickPeriodicInterrupt.h"

void delay(uint32_t milliSeconds)
{
  uint32_t i;
  uint32_t j;

  for (i = 0; i < milliSeconds; i++)
  {
    for (j = 0; j < 1500; j++)
    {
    }
  }
}

StepperMotor MotorPassos(gpio_PTA2, gpio_PTD4, gpio_PTA12, gpio_PTA4);

/*
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

extern "C"
{
  void Systick_Handler(void)
  {
    MotorPassos.doStep();
  }
}
*/

int main(void)
{
  MotorPassos.setStepMode(halfStep);
  MotorPassos.turnOnPowerCoil();
  MotorPassos.setDirectionOfRotation(clock_wise);
  MotorPassos.enableRotation();

  while (true)
  {
    MotorPassos.doStep();
    delay(1);
  }
}
