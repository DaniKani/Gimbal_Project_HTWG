################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.c \
../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.c 

OBJS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o 

C_DEPS += \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d \
./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d 


# Each subdirectory must supply rules for building sources it contributes
chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/%.o chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/%.su chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/%.cyclo: ../chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/%.c chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Domi2/chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-QuaternionMathFunctions

clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-QuaternionMathFunctions:
	-$(RM) ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/QuaternionMathFunctions.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.su ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.cyclo ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o ./chip_headers/CMSIS/CMSIS-DSP-main/CMSIS-DSP-main/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.su

.PHONY: clean-chip_headers-2f-CMSIS-2f-CMSIS-2d-DSP-2d-main-2f-CMSIS-2d-DSP-2d-main-2f-Source-2f-QuaternionMathFunctions

