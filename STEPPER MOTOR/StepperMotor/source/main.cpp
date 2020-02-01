#include "MKL25Z.h"
#include "StepperMotor.h"

StepperMotor MotorPassos(gpio_PTA2, gpio_PTD4, gpio_PTA12, gpio_PTA4);
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

int main(void)
{
    MotorPassos.setStepMode(halfStep);
    MotorPassos.turnOnPowerCoil();
    MotorPassos.setDirectionOfRotation(clock_wise);
    MotorPassos.enableRotation();

    while (true)
    {
        MotorPassos.doStep();
        delay(5000);
    }
}
