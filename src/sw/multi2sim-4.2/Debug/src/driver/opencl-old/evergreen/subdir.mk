################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/opencl-old/evergreen/bin-file.o \
../src/driver/opencl-old/evergreen/command-queue.o \
../src/driver/opencl-old/evergreen/context.o \
../src/driver/opencl-old/evergreen/device.o \
../src/driver/opencl-old/evergreen/event.o \
../src/driver/opencl-old/evergreen/kernel.o \
../src/driver/opencl-old/evergreen/mem.o \
../src/driver/opencl-old/evergreen/opencl.o \
../src/driver/opencl-old/evergreen/platform.o \
../src/driver/opencl-old/evergreen/program.o \
../src/driver/opencl-old/evergreen/repo.o \
../src/driver/opencl-old/evergreen/sampler.o 

C_SRCS += \
../src/driver/opencl-old/evergreen/bin-file.c \
../src/driver/opencl-old/evergreen/command-queue.c \
../src/driver/opencl-old/evergreen/context.c \
../src/driver/opencl-old/evergreen/device.c \
../src/driver/opencl-old/evergreen/event.c \
../src/driver/opencl-old/evergreen/kernel.c \
../src/driver/opencl-old/evergreen/mem.c \
../src/driver/opencl-old/evergreen/opencl.c \
../src/driver/opencl-old/evergreen/platform.c \
../src/driver/opencl-old/evergreen/program.c \
../src/driver/opencl-old/evergreen/repo.c \
../src/driver/opencl-old/evergreen/sampler.c 

OBJS += \
./src/driver/opencl-old/evergreen/bin-file.o \
./src/driver/opencl-old/evergreen/command-queue.o \
./src/driver/opencl-old/evergreen/context.o \
./src/driver/opencl-old/evergreen/device.o \
./src/driver/opencl-old/evergreen/event.o \
./src/driver/opencl-old/evergreen/kernel.o \
./src/driver/opencl-old/evergreen/mem.o \
./src/driver/opencl-old/evergreen/opencl.o \
./src/driver/opencl-old/evergreen/platform.o \
./src/driver/opencl-old/evergreen/program.o \
./src/driver/opencl-old/evergreen/repo.o \
./src/driver/opencl-old/evergreen/sampler.o 

C_DEPS += \
./src/driver/opencl-old/evergreen/bin-file.d \
./src/driver/opencl-old/evergreen/command-queue.d \
./src/driver/opencl-old/evergreen/context.d \
./src/driver/opencl-old/evergreen/device.d \
./src/driver/opencl-old/evergreen/event.d \
./src/driver/opencl-old/evergreen/kernel.d \
./src/driver/opencl-old/evergreen/mem.d \
./src/driver/opencl-old/evergreen/opencl.d \
./src/driver/opencl-old/evergreen/platform.d \
./src/driver/opencl-old/evergreen/program.d \
./src/driver/opencl-old/evergreen/repo.d \
./src/driver/opencl-old/evergreen/sampler.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/opencl-old/evergreen/%.o: ../src/driver/opencl-old/evergreen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


