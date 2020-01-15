#include "mkl_GPIOPort.h"

mkl_GPIOPort blueLed(gpio_PTD1);
mkl_GPIOPort redLed(gpio_PTB18);
mkl_GPIOPort greenLed(gpio_PTB19);

mkl_GPIOPort pushButton(gpio_PTA2);

void setup() {

	blueLed.setPortMode(gpio_output);
	redLed.setPortMode(gpio_output);
	greenLed.setPortMode(gpio_output);

	pushButton.setPortMode(gpio_input);
	pushButton.setPullResistor(gpio_pullUpResistor);
}

int main() {
	uint32_t contador = 0;
	uint8_t select = 0;
	setup();

	while (true) {
		if (pushButton.readBit()) {
			contador++;
			if (contador >= 50000) {
				select++;
				if (select == 3) {
					select = 0;
				}

				contador = 0;
			}

			if (select == 0) {
				redLed.writeBit(0);
				blueLed.writeBit(1);
				greenLed.writeBit(1);
			} else if (select == 1) {
				redLed.writeBit(1);
				blueLed.writeBit(1);
				greenLed.writeBit(0);

			} else if (select == 2) {
				redLed.writeBit(1);
				blueLed.writeBit(0);
				greenLed.writeBit(1);
			}
		} else {
			redLed.writeBit(1);
			blueLed.writeBit(1);
			greenLed.writeBit(1);
		}
	}

	return 0;
}
