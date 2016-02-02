################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/x86/asm/asm.o \
../src/arch/x86/asm/inst.o 

C_SRCS += \
../src/arch/x86/asm/asm.c \
../src/arch/x86/asm/inst.c 

OBJS += \
./src/arch/x86/asm/asm.o \
./src/arch/x86/asm/inst.o 

C_DEPS += \
./src/arch/x86/asm/asm.d \
./src/arch/x86/asm/inst.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/x86/asm/%.o: ../src/arch/x86/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


