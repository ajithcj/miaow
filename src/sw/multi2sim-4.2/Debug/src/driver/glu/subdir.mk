################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/glu/glu-missing.o 

C_SRCS += \
../src/driver/glu/glu-missing.c \
../src/driver/glu/glu.c 

OBJS += \
./src/driver/glu/glu-missing.o \
./src/driver/glu/glu.o 

C_DEPS += \
./src/driver/glu/glu-missing.d \
./src/driver/glu/glu.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/glu/%.o: ../src/driver/glu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


