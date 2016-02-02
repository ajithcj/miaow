################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/mem-system/cache.o \
../src/mem-system/command.o \
../src/mem-system/config.o \
../src/mem-system/directory.o \
../src/mem-system/local-mem-protocol.o \
../src/mem-system/mem-system.o \
../src/mem-system/memory.o \
../src/mem-system/mmu.o \
../src/mem-system/mod-stack.o \
../src/mem-system/module.o \
../src/mem-system/nmoesi-protocol.o \
../src/mem-system/prefetch-history.o \
../src/mem-system/prefetcher.o \
../src/mem-system/spec-mem.o 

C_SRCS += \
../src/mem-system/cache.c \
../src/mem-system/command.c \
../src/mem-system/config.c \
../src/mem-system/directory.c \
../src/mem-system/local-mem-protocol.c \
../src/mem-system/mem-system.c \
../src/mem-system/memory.c \
../src/mem-system/mmu.c \
../src/mem-system/mod-stack.c \
../src/mem-system/module.c \
../src/mem-system/nmoesi-protocol.c \
../src/mem-system/prefetch-history.c \
../src/mem-system/prefetcher.c \
../src/mem-system/spec-mem.c 

OBJS += \
./src/mem-system/cache.o \
./src/mem-system/command.o \
./src/mem-system/config.o \
./src/mem-system/directory.o \
./src/mem-system/local-mem-protocol.o \
./src/mem-system/mem-system.o \
./src/mem-system/memory.o \
./src/mem-system/mmu.o \
./src/mem-system/mod-stack.o \
./src/mem-system/module.o \
./src/mem-system/nmoesi-protocol.o \
./src/mem-system/prefetch-history.o \
./src/mem-system/prefetcher.o \
./src/mem-system/spec-mem.o 

C_DEPS += \
./src/mem-system/cache.d \
./src/mem-system/command.d \
./src/mem-system/config.d \
./src/mem-system/directory.d \
./src/mem-system/local-mem-protocol.d \
./src/mem-system/mem-system.d \
./src/mem-system/memory.d \
./src/mem-system/mmu.d \
./src/mem-system/mod-stack.d \
./src/mem-system/module.d \
./src/mem-system/nmoesi-protocol.d \
./src/mem-system/prefetch-history.d \
./src/mem-system/prefetcher.d \
./src/mem-system/spec-mem.d 


# Each subdirectory must supply rules for building sources it contributes
src/mem-system/%.o: ../src/mem-system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


