################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/arm/emu/context.o \
../src/arch/arm/emu/emu.o \
../src/arch/arm/emu/file.o \
../src/arch/arm/emu/isa.o \
../src/arch/arm/emu/machine.o \
../src/arch/arm/emu/machine_thumb16.o \
../src/arch/arm/emu/machine_thumb32.o \
../src/arch/arm/emu/regs.o \
../src/arch/arm/emu/signal.o \
../src/arch/arm/emu/syscall.o 

C_SRCS += \
../src/arch/arm/emu/context.c \
../src/arch/arm/emu/emu.c \
../src/arch/arm/emu/file.c \
../src/arch/arm/emu/isa.c \
../src/arch/arm/emu/machine.c \
../src/arch/arm/emu/machine_thumb16.c \
../src/arch/arm/emu/machine_thumb32.c \
../src/arch/arm/emu/regs.c \
../src/arch/arm/emu/signal.c \
../src/arch/arm/emu/syscall.c 

OBJS += \
./src/arch/arm/emu/context.o \
./src/arch/arm/emu/emu.o \
./src/arch/arm/emu/file.o \
./src/arch/arm/emu/isa.o \
./src/arch/arm/emu/machine.o \
./src/arch/arm/emu/machine_thumb16.o \
./src/arch/arm/emu/machine_thumb32.o \
./src/arch/arm/emu/regs.o \
./src/arch/arm/emu/signal.o \
./src/arch/arm/emu/syscall.o 

C_DEPS += \
./src/arch/arm/emu/context.d \
./src/arch/arm/emu/emu.d \
./src/arch/arm/emu/file.d \
./src/arch/arm/emu/isa.d \
./src/arch/arm/emu/machine.d \
./src/arch/arm/emu/machine_thumb16.d \
./src/arch/arm/emu/machine_thumb32.d \
./src/arch/arm/emu/regs.d \
./src/arch/arm/emu/signal.d \
./src/arch/arm/emu/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/arm/emu/%.o: ../src/arch/arm/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


