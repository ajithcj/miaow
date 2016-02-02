################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/glew/glew-missing.o 

C_SRCS += \
../src/driver/glew/glew-missing.c \
../src/driver/glew/glew.c 

OBJS += \
./src/driver/glew/glew-missing.o \
./src/driver/glew/glew.o 

C_DEPS += \
./src/driver/glew/glew-missing.d \
./src/driver/glew/glew.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/glew/%.o: ../src/driver/glew/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


