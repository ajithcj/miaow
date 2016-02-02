################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/cuda/api-rt.o \
../runtime/cuda/api.o \
../runtime/cuda/context.o \
../runtime/cuda/debug.o \
../runtime/cuda/device.o \
../runtime/cuda/elf-format.o \
../runtime/cuda/function-arg.o \
../runtime/cuda/function.o \
../runtime/cuda/list.o \
../runtime/cuda/memory.o \
../runtime/cuda/mhandle.o \
../runtime/cuda/module.o \
../runtime/cuda/stream.o 

C_SRCS += \
../runtime/cuda/api-rt.c \
../runtime/cuda/api.c \
../runtime/cuda/context.c \
../runtime/cuda/debug.c \
../runtime/cuda/device.c \
../runtime/cuda/elf-format.c \
../runtime/cuda/function-arg.c \
../runtime/cuda/function.c \
../runtime/cuda/list.c \
../runtime/cuda/memory.c \
../runtime/cuda/mhandle.c \
../runtime/cuda/module.c \
../runtime/cuda/stream.c 

OBJS += \
./runtime/cuda/api-rt.o \
./runtime/cuda/api.o \
./runtime/cuda/context.o \
./runtime/cuda/debug.o \
./runtime/cuda/device.o \
./runtime/cuda/elf-format.o \
./runtime/cuda/function-arg.o \
./runtime/cuda/function.o \
./runtime/cuda/list.o \
./runtime/cuda/memory.o \
./runtime/cuda/mhandle.o \
./runtime/cuda/module.o \
./runtime/cuda/stream.o 

C_DEPS += \
./runtime/cuda/api-rt.d \
./runtime/cuda/api.d \
./runtime/cuda/context.d \
./runtime/cuda/debug.d \
./runtime/cuda/device.d \
./runtime/cuda/elf-format.d \
./runtime/cuda/function-arg.d \
./runtime/cuda/function.d \
./runtime/cuda/list.d \
./runtime/cuda/memory.d \
./runtime/cuda/mhandle.d \
./runtime/cuda/module.d \
./runtime/cuda/stream.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/cuda/%.o: ../runtime/cuda/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


