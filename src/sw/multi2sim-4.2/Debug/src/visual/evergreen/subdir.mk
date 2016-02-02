################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/visual/evergreen/compute-unit.c \
../src/visual/evergreen/gpu.c \
../src/visual/evergreen/inst.c \
../src/visual/evergreen/panel.c \
../src/visual/evergreen/time-dia.c \
../src/visual/evergreen/work-group.c 

OBJS += \
./src/visual/evergreen/compute-unit.o \
./src/visual/evergreen/gpu.o \
./src/visual/evergreen/inst.o \
./src/visual/evergreen/panel.o \
./src/visual/evergreen/time-dia.o \
./src/visual/evergreen/work-group.o 

C_DEPS += \
./src/visual/evergreen/compute-unit.d \
./src/visual/evergreen/gpu.d \
./src/visual/evergreen/inst.d \
./src/visual/evergreen/panel.d \
./src/visual/evergreen/time-dia.d \
./src/visual/evergreen/work-group.d 


# Each subdirectory must supply rules for building sources it contributes
src/visual/evergreen/%.o: ../src/visual/evergreen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


