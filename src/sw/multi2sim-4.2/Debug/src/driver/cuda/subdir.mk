################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/cuda/cuda.o \
../src/driver/cuda/device.o \
../src/driver/cuda/function-arg.o \
../src/driver/cuda/function.o \
../src/driver/cuda/memory.o \
../src/driver/cuda/module.o 

C_SRCS += \
../src/driver/cuda/cuda.c \
../src/driver/cuda/device.c \
../src/driver/cuda/function-arg.c \
../src/driver/cuda/function.c \
../src/driver/cuda/memory.c \
../src/driver/cuda/module.c 

OBJS += \
./src/driver/cuda/cuda.o \
./src/driver/cuda/device.o \
./src/driver/cuda/function-arg.o \
./src/driver/cuda/function.o \
./src/driver/cuda/memory.o \
./src/driver/cuda/module.o 

C_DEPS += \
./src/driver/cuda/cuda.d \
./src/driver/cuda/device.d \
./src/driver/cuda/function-arg.d \
./src/driver/cuda/function.d \
./src/driver/cuda/memory.d \
./src/driver/cuda/module.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/cuda/%.o: ../src/driver/cuda/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


