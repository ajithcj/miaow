################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/evergreen/emu/emu.o \
../src/arch/evergreen/emu/isa.o \
../src/arch/evergreen/emu/machine.o \
../src/arch/evergreen/emu/ndrange.o \
../src/arch/evergreen/emu/opengl-bin-file.o \
../src/arch/evergreen/emu/wavefront.o \
../src/arch/evergreen/emu/work-group.o \
../src/arch/evergreen/emu/work-item.o 

C_SRCS += \
../src/arch/evergreen/emu/emu.c \
../src/arch/evergreen/emu/isa.c \
../src/arch/evergreen/emu/machine.c \
../src/arch/evergreen/emu/ndrange.c \
../src/arch/evergreen/emu/opengl-bin-file.c \
../src/arch/evergreen/emu/wavefront.c \
../src/arch/evergreen/emu/work-group.c \
../src/arch/evergreen/emu/work-item.c 

OBJS += \
./src/arch/evergreen/emu/emu.o \
./src/arch/evergreen/emu/isa.o \
./src/arch/evergreen/emu/machine.o \
./src/arch/evergreen/emu/ndrange.o \
./src/arch/evergreen/emu/opengl-bin-file.o \
./src/arch/evergreen/emu/wavefront.o \
./src/arch/evergreen/emu/work-group.o \
./src/arch/evergreen/emu/work-item.o 

C_DEPS += \
./src/arch/evergreen/emu/emu.d \
./src/arch/evergreen/emu/isa.d \
./src/arch/evergreen/emu/machine.d \
./src/arch/evergreen/emu/ndrange.d \
./src/arch/evergreen/emu/opengl-bin-file.d \
./src/arch/evergreen/emu/wavefront.d \
./src/arch/evergreen/emu/work-group.d \
./src/arch/evergreen/emu/work-item.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/evergreen/emu/%.o: ../src/arch/evergreen/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


