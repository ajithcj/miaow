################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/fermi/asm/asm.o 

C_SRCS += \
../src/arch/fermi/asm/asm.c 

OBJS += \
./src/arch/fermi/asm/asm.o 

C_DEPS += \
./src/arch/fermi/asm/asm.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/fermi/asm/%.o: ../src/arch/fermi/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


