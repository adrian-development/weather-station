################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Firmware/bme680_code.c \
../Firmware/debug.c \
../Firmware/fw_main.c 

OBJS += \
./Firmware/bme680_code.o \
./Firmware/debug.o \
./Firmware/fw_main.o 

C_DEPS += \
./Firmware/bme680_code.d \
./Firmware/debug.d \
./Firmware/fw_main.d 


# Each subdirectory must supply rules for building sources it contributes
Firmware/%.o Firmware/%.su Firmware/%.cyclo: ../Firmware/%.c Firmware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L031xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/adria/Documents/weather-station/Drivers/BME680" -I"C:/Users/adria/Documents/weather-station/Firmware" -Os -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Firmware

clean-Firmware:
	-$(RM) ./Firmware/bme680_code.cyclo ./Firmware/bme680_code.d ./Firmware/bme680_code.o ./Firmware/bme680_code.su ./Firmware/debug.cyclo ./Firmware/debug.d ./Firmware/debug.o ./Firmware/debug.su ./Firmware/fw_main.cyclo ./Firmware/fw_main.d ./Firmware/fw_main.o ./Firmware/fw_main.su

.PHONY: clean-Firmware

