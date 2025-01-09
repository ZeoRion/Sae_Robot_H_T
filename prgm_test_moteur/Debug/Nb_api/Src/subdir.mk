################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Nb_api/Src/can_api.c \
../Nb_api/Src/ihm_api.c \
../Nb_api/Src/nb_adc_api.c \
../Nb_api/Src/nb_api.c \
../Nb_api/Src/nb_bus_api.c \
../Nb_api/Src/nb_dac_api.c \
../Nb_api/Src/nb_pwm_api.c 

OBJS += \
./Nb_api/Src/can_api.o \
./Nb_api/Src/ihm_api.o \
./Nb_api/Src/nb_adc_api.o \
./Nb_api/Src/nb_api.o \
./Nb_api/Src/nb_bus_api.o \
./Nb_api/Src/nb_dac_api.o \
./Nb_api/Src/nb_pwm_api.o 

C_DEPS += \
./Nb_api/Src/can_api.d \
./Nb_api/Src/ihm_api.d \
./Nb_api/Src/nb_adc_api.d \
./Nb_api/Src/nb_api.d \
./Nb_api/Src/nb_bus_api.d \
./Nb_api/Src/nb_dac_api.d \
./Nb_api/Src/nb_pwm_api.d 


# Each subdirectory must supply rules for building sources it contributes
Nb_api/Src/%.o Nb_api/Src/%.su Nb_api/Src/%.cyclo: ../Nb_api/Src/%.c Nb_api/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/travail/Hugo_ROYO/Sae_Robot_H_T/prgm_test_moteur/Common_api/Inc" -I"C:/travail/Hugo_ROYO/Sae_Robot_H_T/prgm_test_moteur/Nb_api/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Nb_api-2f-Src

clean-Nb_api-2f-Src:
	-$(RM) ./Nb_api/Src/can_api.cyclo ./Nb_api/Src/can_api.d ./Nb_api/Src/can_api.o ./Nb_api/Src/can_api.su ./Nb_api/Src/ihm_api.cyclo ./Nb_api/Src/ihm_api.d ./Nb_api/Src/ihm_api.o ./Nb_api/Src/ihm_api.su ./Nb_api/Src/nb_adc_api.cyclo ./Nb_api/Src/nb_adc_api.d ./Nb_api/Src/nb_adc_api.o ./Nb_api/Src/nb_adc_api.su ./Nb_api/Src/nb_api.cyclo ./Nb_api/Src/nb_api.d ./Nb_api/Src/nb_api.o ./Nb_api/Src/nb_api.su ./Nb_api/Src/nb_bus_api.cyclo ./Nb_api/Src/nb_bus_api.d ./Nb_api/Src/nb_bus_api.o ./Nb_api/Src/nb_bus_api.su ./Nb_api/Src/nb_dac_api.cyclo ./Nb_api/Src/nb_dac_api.d ./Nb_api/Src/nb_dac_api.o ./Nb_api/Src/nb_dac_api.su ./Nb_api/Src/nb_pwm_api.cyclo ./Nb_api/Src/nb_pwm_api.d ./Nb_api/Src/nb_pwm_api.o ./Nb_api/Src/nb_pwm_api.su

.PHONY: clean-Nb_api-2f-Src

