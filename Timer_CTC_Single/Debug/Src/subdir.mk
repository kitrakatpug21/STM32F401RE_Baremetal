################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/delay.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer5.c \
../Src/uart2.c 

OBJS += \
./Src/delay.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer5.o \
./Src/uart2.o 

C_DEPS += \
./Src/delay.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer5.d \
./Src/uart2.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -DSTM32F401xE -c -I../Inc -I"F:/ARM/Drivers/CMSIS/Include" -I"F:/ARM/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer5.d ./Src/timer5.o ./Src/timer5.su ./Src/uart2.d ./Src/uart2.o ./Src/uart2.su

.PHONY: clean-Src

