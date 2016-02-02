################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/visual/common/visual-missing.o 

C_SRCS += \
../src/visual/common/cycle-bar.c \
../src/visual/common/led.c \
../src/visual/common/list.c \
../src/visual/common/popup.c \
../src/visual/common/state.c \
../src/visual/common/trace.c \
../src/visual/common/visual-missing.c \
../src/visual/common/visual.c 

OBJS += \
./src/visual/common/cycle-bar.o \
./src/visual/common/led.o \
./src/visual/common/list.o \
./src/visual/common/popup.o \
./src/visual/common/state.o \
./src/visual/common/trace.o \
./src/visual/common/visual-missing.o \
./src/visual/common/visual.o 

C_DEPS += \
./src/visual/common/cycle-bar.d \
./src/visual/common/led.d \
./src/visual/common/list.d \
./src/visual/common/popup.d \
./src/visual/common/state.d \
./src/visual/common/trace.d \
./src/visual/common/visual-missing.d \
./src/visual/common/visual.d 


# Each subdirectory must supply rules for building sources it contributes
src/visual/common/%.o: ../src/visual/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


