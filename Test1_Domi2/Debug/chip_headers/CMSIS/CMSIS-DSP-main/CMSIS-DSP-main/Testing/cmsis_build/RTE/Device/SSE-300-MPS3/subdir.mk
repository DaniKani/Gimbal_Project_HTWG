################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.c 

OBJS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.o 

C_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.d 


# Each subdirectory must supply rules for building sources it contributes
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/%.o chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/%.su chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/%.cyclo: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/%.c chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-SSE-2d-300-2d-MPS3

clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-SSE-2d-300-2d-MPS3:
	-$(RM) ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/startup_fvp_sse300_mps3.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Testing/cmsis_build/RTE/Device/SSE-300-MPS3/system_SSE300MPS3.su

.PHONY: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Testing-2f-cmsis_build-2f-RTE-2f-Device-2f-SSE-2d-300-2d-MPS3

