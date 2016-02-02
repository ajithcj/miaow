################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/arm/asm/asm-thumb.o \
../src/arch/arm/asm/asm.o 

C_SRCS += \
../src/arch/arm/asm/asm-thumb.c \
../src/arch/arm/asm/asm.c 

OBJS += \
./src/arch/arm/asm/asm-thumb.o \
./src/arch/arm/asm/asm.o 

C_DEPS += \
./src/arch/arm/asm/asm-thumb.d \
./src/arch/arm/asm/asm.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/arm/asm/%.o: ../src/arch/arm/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


