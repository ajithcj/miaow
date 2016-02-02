################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/lib/esim/esim.o \
../src/lib/esim/trace.o 

C_SRCS += \
../src/lib/esim/esim.c \
../src/lib/esim/trace.c 

OBJS += \
./src/lib/esim/esim.o \
./src/lib/esim/trace.o 

C_DEPS += \
./src/lib/esim/esim.d \
./src/lib/esim/trace.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/esim/%.o: ../src/lib/esim/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


