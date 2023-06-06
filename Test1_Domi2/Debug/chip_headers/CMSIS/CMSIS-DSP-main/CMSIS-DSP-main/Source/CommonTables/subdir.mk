################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.c 

OBJS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.o 

C_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.d 


# Each subdirectory must supply rules for building sources it contributes
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/%.o chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/%.su chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/%.cyclo: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/%.c chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-CommonTables

clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-CommonTables:
	-$(RM) ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTables.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/CommonTablesF16.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_common_tables_f16.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_const_structs_f16.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/CommonTables/arm_mve_tables_f16.su

.PHONY: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-CommonTables

