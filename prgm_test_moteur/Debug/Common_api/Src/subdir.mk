################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common_api/Src/adc_dac_api.c \
../Common_api/Src/clock_api.c \
../Common_api/Src/error_api.c \
../Common_api/Src/gpio_api.c \
../Common_api/Src/tim_api.c 

OBJS += \
./Common_api/Src/adc_dac_api.o \
./Common_api/Src/clock_api.o \
./Common_api/Src/error_api.o \
./Common_api/Src/gpio_api.o \
./Common_api/Src/tim_api.o 

C_DEPS += \
./Common_api/Src/adc_dac_api.d \
./Common_api/Src/clock_api.d \
./Common_api/Src/error_api.d \
./Common_api/Src/gpio_api.d \
./Common_api/Src/tim_api.d 


# Each subdirectory must supply rules for building sources it contributes
Common_api/Src/%.o Common_api/Src/%.su Common_api/Src/%.cyclo: ../Common_api/Src/%.c Common_api/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/travail/Hugo_ROYO/Sae_Robot_H_T/prgm_test_moteur/Common_api/Inc" -I"C:/travail/Hugo_ROYO/Sae_Robot_H_T/prgm_test_moteur/Nb_api/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common_api-2f-Src

clean-Common_api-2f-Src:
	-$(RM) ./Common_api/Src/adc_dac_api.cyclo ./Common_api/Src/adc_dac_api.d ./Common_api/Src/adc_dac_api.o ./Common_api/Src/adc_dac_api.su ./Common_api/Src/clock_api.cyclo ./Common_api/Src/clock_api.d ./Common_api/Src/clock_api.o ./Common_api/Src/clock_api.su ./Common_api/Src/error_api.cyclo ./Common_api/Src/error_api.d ./Common_api/Src/error_api.o ./Common_api/Src/error_api.su ./Common_api/Src/gpio_api.cyclo ./Common_api/Src/gpio_api.d ./Common_api/Src/gpio_api.o ./Common_api/Src/gpio_api.su ./Common_api/Src/tim_api.cyclo ./Common_api/Src/tim_api.d ./Common_api/Src/tim_api.o ./Common_api/Src/tim_api.su

.PHONY: clean-Common_api-2f-Src

