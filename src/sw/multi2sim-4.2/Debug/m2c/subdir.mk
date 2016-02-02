################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/m2c.o 

C_SRCS += \
../m2c/m2c.c 

OBJS += \
./m2c/m2c.o 

C_DEPS += \
./m2c/m2c.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/%.o: ../m2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


