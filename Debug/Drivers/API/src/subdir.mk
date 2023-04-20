################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/lib_dht11.c \
../Drivers/API/src/lib_lcd_16x02_i2c.c 

OBJS += \
./Drivers/API/src/lib_dht11.o \
./Drivers/API/src/lib_lcd_16x02_i2c.o 

C_DEPS += \
./Drivers/API/src/lib_dht11.d \
./Drivers/API/src/lib_lcd_16x02_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o Drivers/API/src/%.su Drivers/API/src/%.cyclo: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/palmaventura/STM32CubeIDE/Project/Proyecto_Drivers/Core/Src" -I"/home/palmaventura/STM32CubeIDE/Project/Proyecto_Drivers/Drivers" -I"/home/palmaventura/STM32CubeIDE/Project/Proyecto_Drivers/Drivers/API" -I"/home/palmaventura/STM32CubeIDE/Project/Proyecto_Drivers/Drivers/API/inc" -I"/home/palmaventura/STM32CubeIDE/Project/Proyecto_Drivers/Drivers/API/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-src

clean-Drivers-2f-API-2f-src:
	-$(RM) ./Drivers/API/src/lib_dht11.cyclo ./Drivers/API/src/lib_dht11.d ./Drivers/API/src/lib_dht11.o ./Drivers/API/src/lib_dht11.su ./Drivers/API/src/lib_lcd_16x02_i2c.cyclo ./Drivers/API/src/lib_lcd_16x02_i2c.d ./Drivers/API/src/lib_lcd_16x02_i2c.o ./Drivers/API/src/lib_lcd_16x02_i2c.su

.PHONY: clean-Drivers-2f-API-2f-src

