################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/gl/gl-missing.o 

C_SRCS += \
../m2c/gl/gl-missing.c \
../m2c/gl/gl.c 

OBJS += \
./m2c/gl/gl-missing.o \
./m2c/gl/gl.o 

C_DEPS += \
./m2c/gl/gl-missing.d \
./m2c/gl/gl.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/gl/%.o: ../m2c/gl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


