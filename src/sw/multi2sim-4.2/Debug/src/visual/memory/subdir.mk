################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/visual/memory/mem-system.c \
../src/visual/memory/mod-access.c \
../src/visual/memory/mod-widget.c \
../src/visual/memory/mod.c \
../src/visual/memory/net.c \
../src/visual/memory/panel.c 

OBJS += \
./src/visual/memory/mem-system.o \
./src/visual/memory/mod-access.o \
./src/visual/memory/mod-widget.o \
./src/visual/memory/mod.o \
./src/visual/memory/net.o \
./src/visual/memory/panel.o 

C_DEPS += \
./src/visual/memory/mem-system.d \
./src/visual/memory/mod-access.d \
./src/visual/memory/mod-widget.d \
./src/visual/memory/mod.d \
./src/visual/memory/net.d \
./src/visual/memory/panel.d 


# Each subdirectory must supply rules for building sources it contributes
src/visual/memory/%.o: ../src/visual/memory/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


