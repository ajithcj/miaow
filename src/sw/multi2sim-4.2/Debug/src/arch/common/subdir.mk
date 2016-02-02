################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/common/arch.o \
../src/arch/common/asm.o \
../src/arch/common/emu.o \
../src/arch/common/runtime.o \
../src/arch/common/timing.o 

C_SRCS += \
../src/arch/common/arch.c \
../src/arch/common/asm.c \
../src/arch/common/emu.c \
../src/arch/common/runtime.c \
../src/arch/common/timing.c 

OBJS += \
./src/arch/common/arch.o \
./src/arch/common/asm.o \
./src/arch/common/emu.o \
./src/arch/common/runtime.o \
./src/arch/common/timing.o 

C_DEPS += \
./src/arch/common/arch.d \
./src/arch/common/asm.d \
./src/arch/common/emu.d \
./src/arch/common/runtime.d \
./src/arch/common/timing.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/common/%.o: ../src/arch/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


