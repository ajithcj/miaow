################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/visual/southern-islands/compute-unit.c \
../src/visual/southern-islands/gpu.c \
../src/visual/southern-islands/inst.c \
../src/visual/southern-islands/panel.c \
../src/visual/southern-islands/time-dia.c \
../src/visual/southern-islands/work-group.c 

OBJS += \
./src/visual/southern-islands/compute-unit.o \
./src/visual/southern-islands/gpu.o \
./src/visual/southern-islands/inst.o \
./src/visual/southern-islands/panel.o \
./src/visual/southern-islands/time-dia.o \
./src/visual/southern-islands/work-group.o 

C_DEPS += \
./src/visual/southern-islands/compute-unit.d \
./src/visual/southern-islands/gpu.d \
./src/visual/southern-islands/inst.d \
./src/visual/southern-islands/panel.d \
./src/visual/southern-islands/time-dia.d \
./src/visual/southern-islands/work-group.d 


# Each subdirectory must supply rules for building sources it contributes
src/visual/southern-islands/%.o: ../src/visual/southern-islands/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


