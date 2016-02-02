################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/kepler/asm/asm.o 

C_SRCS += \
../src/arch/kepler/asm/asm.c 

OBJS += \
./src/arch/kepler/asm/asm.o 

C_DEPS += \
./src/arch/kepler/asm/asm.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/kepler/asm/%.o: ../src/arch/kepler/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


