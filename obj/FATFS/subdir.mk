################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/diskio.c \
../FATFS/hw_spi.c \
../FATFS/pff.c 

OBJS += \
./FATFS/diskio.o \
./FATFS/hw_spi.o \
./FATFS/pff.o 

C_DEPS += \
./FATFS/diskio.d \
./FATFS/hw_spi.d \
./FATFS/pff.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/%.o: ../FATFS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/aptex96/mrs_community-workspace/ZoulOS/Debug" -I"/home/aptex96/mrs_community-workspace/ZoulOS/Core" -I"/home/aptex96/mrs_community-workspace/ZoulOS/User" -I"/home/aptex96/mrs_community-workspace/ZoulOS/Peripheral/inc" -I"/home/aptex96/mrs_community-workspace/ZoulOS/FATFS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


