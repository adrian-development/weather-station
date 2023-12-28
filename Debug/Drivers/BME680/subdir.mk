################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BME680/bme68x.c 

OBJS += \
./Drivers/BME680/bme68x.o 

C_DEPS += \
./Drivers/BME680/bme68x.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BME680/%.o Drivers/BME680/%.su Drivers/BME680/%.cyclo: ../Drivers/BME680/%.c Drivers/BME680/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/adria/Documents/weather-station/Drivers/BME680" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BME680

clean-Drivers-2f-BME680:
	-$(RM) ./Drivers/BME680/bme68x.cyclo ./Drivers/BME680/bme68x.d ./Drivers/BME680/bme68x.o ./Drivers/BME680/bme68x.su

.PHONY: clean-Drivers-2f-BME680

