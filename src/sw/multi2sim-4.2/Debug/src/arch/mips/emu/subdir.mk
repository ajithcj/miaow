################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/mips/emu/context.o \
../src/arch/mips/emu/emu.o \
../src/arch/mips/emu/file.o \
../src/arch/mips/emu/isa.o \
../src/arch/mips/emu/machine.o \
../src/arch/mips/emu/regs.o \
../src/arch/mips/emu/syscall.o 

C_SRCS += \
../src/arch/mips/emu/context.c \
../src/arch/mips/emu/emu.c \
../src/arch/mips/emu/file.c \
../src/arch/mips/emu/isa.c \
../src/arch/mips/emu/machine.c \
../src/arch/mips/emu/regs.c \
../src/arch/mips/emu/syscall.c 

OBJS += \
./src/arch/mips/emu/context.o \
./src/arch/mips/emu/emu.o \
./src/arch/mips/emu/file.o \
./src/arch/mips/emu/isa.o \
./src/arch/mips/emu/machine.o \
./src/arch/mips/emu/regs.o \
./src/arch/mips/emu/syscall.o 

C_DEPS += \
./src/arch/mips/emu/context.d \
./src/arch/mips/emu/emu.d \
./src/arch/mips/emu/file.d \
./src/arch/mips/emu/isa.d \
./src/arch/mips/emu/machine.d \
./src/arch/mips/emu/regs.d \
./src/arch/mips/emu/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/mips/emu/%.o: ../src/arch/mips/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


