################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/glew/api.o \
../runtime/glew/debug.o \
../runtime/glew/mhandle.o 

C_SRCS += \
../runtime/glew/api.c \
../runtime/glew/debug.c \
../runtime/glew/mhandle.c 

OBJS += \
./runtime/glew/api.o \
./runtime/glew/debug.o \
./runtime/glew/mhandle.o 

C_DEPS += \
./runtime/glew/api.d \
./runtime/glew/debug.d \
./runtime/glew/mhandle.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/glew/%.o: ../runtime/glew/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


