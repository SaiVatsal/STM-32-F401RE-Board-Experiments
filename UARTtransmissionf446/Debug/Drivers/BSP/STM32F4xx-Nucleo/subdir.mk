################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F4xx-Nucleo/%.o Drivers/BSP/STM32F4xx-Nucleo/%.su Drivers/BSP/STM32F4xx-Nucleo/%.cyclo: ../Drivers/BSP/STM32F4xx-Nucleo/%.c Drivers/BSP/STM32F4xx-Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32F4xx-Nucleo -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo

clean-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo:
	-$(RM) ./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.cyclo ./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.d ./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.o ./Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo

