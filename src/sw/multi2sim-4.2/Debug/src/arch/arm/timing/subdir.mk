################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/arm/timing/cpu.o 

C_SRCS += \
../src/arch/arm/timing/cpu.c 

OBJS += \
./src/arch/arm/timing/cpu.o 

C_DEPS += \
./src/arch/arm/timing/cpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/arm/timing/%.o: ../src/arch/arm/timing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


