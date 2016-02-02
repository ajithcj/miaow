################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/evergreen/asm/asm-dump.o \
../src/arch/evergreen/asm/asm.o 

C_SRCS += \
../src/arch/evergreen/asm/asm-dump.c \
../src/arch/evergreen/asm/asm.c 

OBJS += \
./src/arch/evergreen/asm/asm-dump.o \
./src/arch/evergreen/asm/asm.o 

C_DEPS += \
./src/arch/evergreen/asm/asm-dump.d \
./src/arch/evergreen/asm/asm.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/evergreen/asm/%.o: ../src/arch/evergreen/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


