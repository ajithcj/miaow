################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/fermi/emu/emu.o \
../src/arch/fermi/emu/grid.o \
../src/arch/fermi/emu/isa.o \
../src/arch/fermi/emu/machine.o \
../src/arch/fermi/emu/thread-block.o \
../src/arch/fermi/emu/thread.o \
../src/arch/fermi/emu/warp.o 

C_SRCS += \
../src/arch/fermi/emu/emu.c \
../src/arch/fermi/emu/grid.c \
../src/arch/fermi/emu/isa.c \
../src/arch/fermi/emu/machine.c \
../src/arch/fermi/emu/thread-block.c \
../src/arch/fermi/emu/thread.c \
../src/arch/fermi/emu/warp.c 

OBJS += \
./src/arch/fermi/emu/emu.o \
./src/arch/fermi/emu/grid.o \
./src/arch/fermi/emu/isa.o \
./src/arch/fermi/emu/machine.o \
./src/arch/fermi/emu/thread-block.o \
./src/arch/fermi/emu/thread.o \
./src/arch/fermi/emu/warp.o 

C_DEPS += \
./src/arch/fermi/emu/emu.d \
./src/arch/fermi/emu/grid.d \
./src/arch/fermi/emu/isa.d \
./src/arch/fermi/emu/machine.d \
./src/arch/fermi/emu/thread-block.d \
./src/arch/fermi/emu/thread.d \
./src/arch/fermi/emu/warp.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/fermi/emu/%.o: ../src/arch/fermi/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


