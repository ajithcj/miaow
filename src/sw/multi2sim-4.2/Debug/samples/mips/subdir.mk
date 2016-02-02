################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../samples/mips/test-args.c \
../samples/mips/test-sort.c 

OBJS += \
./samples/mips/test-args.o \
./samples/mips/test-sort.o 

C_DEPS += \
./samples/mips/test-args.d \
./samples/mips/test-sort.d 


# Each subdirectory must supply rules for building sources it contributes
samples/mips/%.o: ../samples/mips/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


