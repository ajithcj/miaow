################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/amd/amd-missing.o 

C_SRCS += \
../m2c/amd/amd-missing.c \
../m2c/amd/amd.c 

OBJS += \
./m2c/amd/amd-missing.o \
./m2c/amd/amd.o 

C_DEPS += \
./m2c/amd/amd-missing.d \
./m2c/amd/amd.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/amd/%.o: ../m2c/amd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


