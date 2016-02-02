################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/opencl/opencl.o \
../src/driver/opencl/si-kernel.o \
../src/driver/opencl/si-program.o 

C_SRCS += \
../src/driver/opencl/opencl.c \
../src/driver/opencl/si-kernel.c \
../src/driver/opencl/si-program.c 

OBJS += \
./src/driver/opencl/opencl.o \
./src/driver/opencl/si-kernel.o \
./src/driver/opencl/si-program.o 

C_DEPS += \
./src/driver/opencl/opencl.d \
./src/driver/opencl/si-kernel.d \
./src/driver/opencl/si-program.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/opencl/%.o: ../src/driver/opencl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


