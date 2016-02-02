################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/southern-islands/emu/emu.o \
../src/arch/southern-islands/emu/isa.o \
../src/arch/southern-islands/emu/machine.o \
../src/arch/southern-islands/emu/ndrange.o \
../src/arch/southern-islands/emu/opengl-bin-file.o \
../src/arch/southern-islands/emu/wavefront.o \
../src/arch/southern-islands/emu/work-group.o \
../src/arch/southern-islands/emu/work-item.o 

C_SRCS += \
../src/arch/southern-islands/emu/emu.c \
../src/arch/southern-islands/emu/isa.c \
../src/arch/southern-islands/emu/machine.c \
../src/arch/southern-islands/emu/ndrange.c \
../src/arch/southern-islands/emu/opengl-bin-file.c \
../src/arch/southern-islands/emu/wavefront.c \
../src/arch/southern-islands/emu/work-group.c \
../src/arch/southern-islands/emu/work-item.c 

OBJS += \
./src/arch/southern-islands/emu/emu.o \
./src/arch/southern-islands/emu/isa.o \
./src/arch/southern-islands/emu/machine.o \
./src/arch/southern-islands/emu/ndrange.o \
./src/arch/southern-islands/emu/opengl-bin-file.o \
./src/arch/southern-islands/emu/wavefront.o \
./src/arch/southern-islands/emu/work-group.o \
./src/arch/southern-islands/emu/work-item.o 

C_DEPS += \
./src/arch/southern-islands/emu/emu.d \
./src/arch/southern-islands/emu/isa.d \
./src/arch/southern-islands/emu/machine.d \
./src/arch/southern-islands/emu/ndrange.d \
./src/arch/southern-islands/emu/opengl-bin-file.d \
./src/arch/southern-islands/emu/wavefront.d \
./src/arch/southern-islands/emu/work-group.d \
./src/arch/southern-islands/emu/work-item.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/southern-islands/emu/%.o: ../src/arch/southern-islands/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


