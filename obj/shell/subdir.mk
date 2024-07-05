################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../shell/commands.c \
../shell/hexedit.c \
../shell/mcurses.c \
../shell/shell.c 

OBJS += \
./shell/commands.o \
./shell/hexedit.o \
./shell/mcurses.o \
./shell/shell.o 

C_DEPS += \
./shell/commands.d \
./shell/hexedit.d \
./shell/mcurses.d \
./shell/shell.d 


# Each subdirectory must supply rules for building sources it contributes
shell/%.o: ../shell/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/aptex96/mrs_community-workspace/ZoulOS/Debug" -I"/home/aptex96/mrs_community-workspace/ZoulOS/Core" -I"/home/aptex96/mrs_community-workspace/ZoulOS/User" -I"/home/aptex96/mrs_community-workspace/ZoulOS/Peripheral/inc" -I"/home/aptex96/mrs_community-workspace/ZoulOS/kernel" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


