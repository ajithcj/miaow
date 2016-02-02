################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../samples/x86/test-args.c \
../samples/x86/test-sort.c \
../samples/x86/test-threads.c 

OBJS += \
./samples/x86/test-args.o \
./samples/x86/test-sort.o \
./samples/x86/test-threads.o 

C_DEPS += \
./samples/x86/test-args.d \
./samples/x86/test-sort.d \
./samples/x86/test-threads.d 


# Each subdirectory must supply rules for building sources it contributes
samples/x86/%.o: ../samples/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


