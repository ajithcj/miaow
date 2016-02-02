################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/visual/x86/context.c \
../src/visual/x86/core.c \
../src/visual/x86/cpu.c \
../src/visual/x86/inst.c \
../src/visual/x86/panel.c \
../src/visual/x86/time-dia.c 

OBJS += \
./src/visual/x86/context.o \
./src/visual/x86/core.o \
./src/visual/x86/cpu.o \
./src/visual/x86/inst.o \
./src/visual/x86/panel.o \
./src/visual/x86/time-dia.o 

C_DEPS += \
./src/visual/x86/context.d \
./src/visual/x86/core.d \
./src/visual/x86/cpu.d \
./src/visual/x86/inst.d \
./src/visual/x86/panel.d \
./src/visual/x86/time-dia.d 


# Each subdirectory must supply rules for building sources it contributes
src/visual/x86/%.o: ../src/visual/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


