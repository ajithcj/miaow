################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/opencl/command-queue.o \
../runtime/opencl/command.o \
../runtime/opencl/context.o \
../runtime/opencl/debug.o \
../runtime/opencl/device.o \
../runtime/opencl/elf-format.o \
../runtime/opencl/even-partition-strategy.o \
../runtime/opencl/event.o \
../runtime/opencl/evg-device.o \
../runtime/opencl/evg-kernel.o \
../runtime/opencl/evg-program.o \
../runtime/opencl/kernel.o \
../runtime/opencl/list.o \
../runtime/opencl/mem.o \
../runtime/opencl/mhandle.o \
../runtime/opencl/misc.o \
../runtime/opencl/object.o \
../runtime/opencl/opencl.o \
../runtime/opencl/partition-strategy.o \
../runtime/opencl/partition-util-time.o \
../runtime/opencl/partition-util.o \
../runtime/opencl/platform.o \
../runtime/opencl/program.o \
../runtime/opencl/relative-runtime-partition-strategy.o \
../runtime/opencl/sampler.o \
../runtime/opencl/si-device.o \
../runtime/opencl/si-kernel.o \
../runtime/opencl/si-program.o \
../runtime/opencl/string.o \
../runtime/opencl/thread-list.o \
../runtime/opencl/union-device.o \
../runtime/opencl/union-kernel.o \
../runtime/opencl/union-program.o \
../runtime/opencl/x86-device-wi.o \
../runtime/opencl/x86-device.o \
../runtime/opencl/x86-kernel.o \
../runtime/opencl/x86-program.o 

C_SRCS += \
../runtime/opencl/command-queue.c \
../runtime/opencl/command.c \
../runtime/opencl/context.c \
../runtime/opencl/debug.c \
../runtime/opencl/device.c \
../runtime/opencl/elf-format.c \
../runtime/opencl/even-partition-strategy.c \
../runtime/opencl/event.c \
../runtime/opencl/evg-device.c \
../runtime/opencl/evg-kernel.c \
../runtime/opencl/evg-program.c \
../runtime/opencl/kernel.c \
../runtime/opencl/list.c \
../runtime/opencl/mem.c \
../runtime/opencl/mhandle.c \
../runtime/opencl/misc.c \
../runtime/opencl/object.c \
../runtime/opencl/opencl.c \
../runtime/opencl/partition-strategy.c \
../runtime/opencl/partition-util-time.c \
../runtime/opencl/partition-util.c \
../runtime/opencl/platform.c \
../runtime/opencl/program.c \
../runtime/opencl/relative-runtime-partition-strategy.c \
../runtime/opencl/sampler.c \
../runtime/opencl/si-device.c \
../runtime/opencl/si-kernel.c \
../runtime/opencl/si-program.c \
../runtime/opencl/string.c \
../runtime/opencl/thread-list.c \
../runtime/opencl/union-device.c \
../runtime/opencl/union-kernel.c \
../runtime/opencl/union-program.c \
../runtime/opencl/x86-device.c \
../runtime/opencl/x86-kernel.c \
../runtime/opencl/x86-program.c 

OBJS += \
./runtime/opencl/command-queue.o \
./runtime/opencl/command.o \
./runtime/opencl/context.o \
./runtime/opencl/debug.o \
./runtime/opencl/device.o \
./runtime/opencl/elf-format.o \
./runtime/opencl/even-partition-strategy.o \
./runtime/opencl/event.o \
./runtime/opencl/evg-device.o \
./runtime/opencl/evg-kernel.o \
./runtime/opencl/evg-program.o \
./runtime/opencl/kernel.o \
./runtime/opencl/list.o \
./runtime/opencl/mem.o \
./runtime/opencl/mhandle.o \
./runtime/opencl/misc.o \
./runtime/opencl/object.o \
./runtime/opencl/opencl.o \
./runtime/opencl/partition-strategy.o \
./runtime/opencl/partition-util-time.o \
./runtime/opencl/partition-util.o \
./runtime/opencl/platform.o \
./runtime/opencl/program.o \
./runtime/opencl/relative-runtime-partition-strategy.o \
./runtime/opencl/sampler.o \
./runtime/opencl/si-device.o \
./runtime/opencl/si-kernel.o \
./runtime/opencl/si-program.o \
./runtime/opencl/string.o \
./runtime/opencl/thread-list.o \
./runtime/opencl/union-device.o \
./runtime/opencl/union-kernel.o \
./runtime/opencl/union-program.o \
./runtime/opencl/x86-device.o \
./runtime/opencl/x86-kernel.o \
./runtime/opencl/x86-program.o 

C_DEPS += \
./runtime/opencl/command-queue.d \
./runtime/opencl/command.d \
./runtime/opencl/context.d \
./runtime/opencl/debug.d \
./runtime/opencl/device.d \
./runtime/opencl/elf-format.d \
./runtime/opencl/even-partition-strategy.d \
./runtime/opencl/event.d \
./runtime/opencl/evg-device.d \
./runtime/opencl/evg-kernel.d \
./runtime/opencl/evg-program.d \
./runtime/opencl/kernel.d \
./runtime/opencl/list.d \
./runtime/opencl/mem.d \
./runtime/opencl/mhandle.d \
./runtime/opencl/misc.d \
./runtime/opencl/object.d \
./runtime/opencl/opencl.d \
./runtime/opencl/partition-strategy.d \
./runtime/opencl/partition-util-time.d \
./runtime/opencl/partition-util.d \
./runtime/opencl/platform.d \
./runtime/opencl/program.d \
./runtime/opencl/relative-runtime-partition-strategy.d \
./runtime/opencl/sampler.d \
./runtime/opencl/si-device.d \
./runtime/opencl/si-kernel.d \
./runtime/opencl/si-program.d \
./runtime/opencl/string.d \
./runtime/opencl/thread-list.d \
./runtime/opencl/union-device.d \
./runtime/opencl/union-kernel.d \
./runtime/opencl/union-program.d \
./runtime/opencl/x86-device.d \
./runtime/opencl/x86-kernel.d \
./runtime/opencl/x86-program.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/opencl/%.o: ../runtime/opencl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


