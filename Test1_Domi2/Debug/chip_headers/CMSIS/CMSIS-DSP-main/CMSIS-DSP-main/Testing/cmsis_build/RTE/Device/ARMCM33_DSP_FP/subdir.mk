################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.c 

S_UPPER_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.S 

OBJS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.o 

S_UPPER_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.d 

C_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.d 


# Each subdirectory must supply rules for building sources it contributes
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.o: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.S chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.o chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.su chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.cyclo: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/%.c chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP

clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP:
	-$(RM) ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/startup_ARMCM33.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/ARMCM33_DSP_FP/system_ARMCM33.su

.PHONY: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP

