################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/opencl-old/api.o \
../runtime/opencl-old/command-queue.o \
../runtime/opencl-old/context.o \
../runtime/opencl-old/debug.o \
../runtime/opencl-old/device.o \
../runtime/opencl-old/event.o \
../runtime/opencl-old/kernel.o \
../runtime/opencl-old/mem.o \
../runtime/opencl-old/mhandle.o \
../runtime/opencl-old/platform.o \
../runtime/opencl-old/program.o \
../runtime/opencl-old/sampler.o 

C_SRCS += \
../runtime/opencl-old/api.c \
../runtime/opencl-old/command-queue.c \
../runtime/opencl-old/context.c \
../runtime/opencl-old/debug.c \
../runtime/opencl-old/device.c \
../runtime/opencl-old/event.c \
../runtime/opencl-old/kernel.c \
../runtime/opencl-old/mem.c \
../runtime/opencl-old/mhandle.c \
../runtime/opencl-old/platform.c \
../runtime/opencl-old/program.c \
../runtime/opencl-old/sampler.c 

OBJS += \
./runtime/opencl-old/api.o \
./runtime/opencl-old/command-queue.o \
./runtime/opencl-old/context.o \
./runtime/opencl-old/debug.o \
./runtime/opencl-old/device.o \
./runtime/opencl-old/event.o \
./runtime/opencl-old/kernel.o \
./runtime/opencl-old/mem.o \
./runtime/opencl-old/mhandle.o \
./runtime/opencl-old/platform.o \
./runtime/opencl-old/program.o \
./runtime/opencl-old/sampler.o 

C_DEPS += \
./runtime/opencl-old/api.d \
./runtime/opencl-old/command-queue.d \
./runtime/opencl-old/context.d \
./runtime/opencl-old/debug.d \
./runtime/opencl-old/device.d \
./runtime/opencl-old/event.d \
./runtime/opencl-old/kernel.d \
./runtime/opencl-old/mem.d \
./runtime/opencl-old/mhandle.d \
./runtime/opencl-old/platform.d \
./runtime/opencl-old/program.d \
./runtime/opencl-old/sampler.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/opencl-old/%.o: ../runtime/opencl-old/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


