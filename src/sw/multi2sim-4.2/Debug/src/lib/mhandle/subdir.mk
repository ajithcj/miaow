################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/lib/mhandle/mhandle.o 

C_SRCS += \
../src/lib/mhandle/mhandle.c 

OBJS += \
./src/lib/mhandle/mhandle.o 

C_DEPS += \
./src/lib/mhandle/mhandle.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/mhandle/%.o: ../src/lib/mhandle/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


