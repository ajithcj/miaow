################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/network/buffer.o \
../src/network/bus.o \
../src/network/command.o \
../src/network/link.o \
../src/network/message.o \
../src/network/net-system.o \
../src/network/network.o \
../src/network/node.o \
../src/network/routing-table.o \
../src/network/visual.o 

C_SRCS += \
../src/network/buffer.c \
../src/network/bus.c \
../src/network/command.c \
../src/network/link.c \
../src/network/message.c \
../src/network/net-system.c \
../src/network/network.c \
../src/network/node.c \
../src/network/routing-table.c \
../src/network/visual.c 

OBJS += \
./src/network/buffer.o \
./src/network/bus.o \
./src/network/command.o \
./src/network/link.o \
./src/network/message.o \
./src/network/net-system.o \
./src/network/network.o \
./src/network/node.o \
./src/network/routing-table.o \
./src/network/visual.o 

C_DEPS += \
./src/network/buffer.d \
./src/network/bus.d \
./src/network/command.d \
./src/network/link.d \
./src/network/message.d \
./src/network/net-system.d \
./src/network/network.d \
./src/network/node.d \
./src/network/routing-table.d \
./src/network/visual.d 


# Each subdirectory must supply rules for building sources it contributes
src/network/%.o: ../src/network/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


