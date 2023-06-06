################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.c 

OBJS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.o 

C_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.d 


# Each subdirectory must supply rules for building sources it contributes
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/%.o chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/%.su chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/%.cyclo: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/%.c chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Examples-2f-ARM-2f-arm_class_marks_example-2f-RTE-2f-Device-2f-ARMCM0

clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Examples-2f-ARM-2f-arm_class_marks_example-2f-RTE-2f-Device-2f-ARMCM0:
	-$(RM) ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/startup_ARMCM0.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Examples/ARM/arm_class_marks_example/RTE/Device/ARMCM0/system_ARMCM0.su

.PHONY: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Examples-2f-ARM-2f-arm_class_marks_example-2f-RTE-2f-Device-2f-ARMCM0

