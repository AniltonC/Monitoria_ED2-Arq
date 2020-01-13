################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/cpp_config.cpp \
../source/main.cpp \
../source/mkl_GPIO.cpp \
../source/mkl_GPIOPort.cpp 

C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/cpp_config.o \
./source/main.o \
./source/mkl_GPIO.o \
./source/mkl_GPIOPort.o \
./source/mtb.o \
./source/semihost_hardfault.o 

CPP_DEPS += \
./source/cpp_config.d \
./source/main.d \
./source/mkl_GPIO.d \
./source/mkl_GPIOPort.d 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VFM4_cm0plus -DCPU_MKL25Z128VFM4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\board" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\source" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\drivers" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\CMSIS" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\utilities" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VFM4_cm0plus -DCPU_MKL25Z128VFM4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\board" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\source" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\drivers" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\CMSIS" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\utilities" -I"C:\Users\anilt\Desktop\Git Repositories\Monitoria_ED2-Arq\GPIO PORT MCUXpresso - Test Version\GPIO Port\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


