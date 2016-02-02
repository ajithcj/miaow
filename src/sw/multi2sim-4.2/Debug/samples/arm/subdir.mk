################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../samples/arm/test-args.c \
../samples/arm/test-sort.c 

OBJS += \
./samples/arm/test-args.o \
./samples/arm/test-sort.o 

C_DEPS += \
./samples/arm/test-args.d \
./samples/arm/test-sort.d 


# Each subdirectory must supply rules for building sources it contributes
samples/arm/%.o: ../samples/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


