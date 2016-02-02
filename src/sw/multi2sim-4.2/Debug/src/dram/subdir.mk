################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/dram/bank.o \
../src/dram/command.o \
../src/dram/controller.o \
../src/dram/dram-system.o \
../src/dram/dram.o \
../src/dram/file-accessor.o \
../src/dram/rank.o \
../src/dram/request.o 

C_SRCS += \
../src/dram/bank.c \
../src/dram/command.c \
../src/dram/controller.c \
../src/dram/dram-system.c \
../src/dram/dram.c \
../src/dram/file-accessor.c \
../src/dram/rank.c \
../src/dram/request.c 

OBJS += \
./src/dram/bank.o \
./src/dram/command.o \
./src/dram/controller.o \
./src/dram/dram-system.o \
./src/dram/dram.o \
./src/dram/file-accessor.o \
./src/dram/rank.o \
./src/dram/request.o 

C_DEPS += \
./src/dram/bank.d \
./src/dram/command.d \
./src/dram/controller.d \
./src/dram/dram-system.d \
./src/dram/dram.d \
./src/dram/file-accessor.d \
./src/dram/rank.d \
./src/dram/request.d 


# Each subdirectory must supply rules for building sources it contributes
src/dram/%.o: ../src/dram/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


