################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/EKF.c \
../Src/Gyr_Acc_Calibration.c \
../Src/adc_dma.c \
../Src/dma.c \
../Src/main.c \
../Src/mpu9250.c \
../Src/spi_dma.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/tim_sample_mpu.c \
../Src/uart.c \
../Src/uart_dma.c 

OBJS += \
./Src/EKF.o \
./Src/Gyr_Acc_Calibration.o \
./Src/adc_dma.o \
./Src/dma.o \
./Src/main.o \
./Src/mpu9250.o \
./Src/spi_dma.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/tim_sample_mpu.o \
./Src/uart.o \
./Src/uart_dma.o 

C_DEPS += \
./Src/EKF.d \
./Src/Gyr_Acc_Calibration.d \
./Src/adc_dma.d \
./Src/dma.d \
./Src/main.d \
./Src/mpu9250.d \
./Src/spi_dma.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/tim_sample_mpu.d \
./Src/uart.d \
./Src/uart_dma.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Dani/chip_headers/CMSIS/Include" -I"C:/Users/Domin/Documents/GitHub/Gimbal_Project_HTWG/Test1_Dani/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/EKF.cyclo ./Src/EKF.d ./Src/EKF.o ./Src/EKF.su ./Src/Gyr_Acc_Calibration.cyclo ./Src/Gyr_Acc_Calibration.d ./Src/Gyr_Acc_Calibration.o ./Src/Gyr_Acc_Calibration.su ./Src/adc_dma.cyclo ./Src/adc_dma.d ./Src/adc_dma.o ./Src/adc_dma.su ./Src/dma.cyclo ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/mpu9250.cyclo ./Src/mpu9250.d ./Src/mpu9250.o ./Src/mpu9250.su ./Src/spi_dma.cyclo ./Src/spi_dma.d ./Src/spi_dma.o ./Src/spi_dma.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/tim_sample_mpu.cyclo ./Src/tim_sample_mpu.d ./Src/tim_sample_mpu.o ./Src/tim_sample_mpu.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su ./Src/uart_dma.cyclo ./Src/uart_dma.d ./Src/uart_dma.o ./Src/uart_dma.su

.PHONY: clean-Src

