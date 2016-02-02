################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/southern-islands/asm/arg.o \
../src/arch/southern-islands/asm/asm.o \
../src/arch/southern-islands/asm/bin-file.o \
../src/arch/southern-islands/asm/input.o 

C_SRCS += \
../src/arch/southern-islands/asm/arg.c \
../src/arch/southern-islands/asm/asm.c \
../src/arch/southern-islands/asm/bin-file.c \
../src/arch/southern-islands/asm/input.c 

OBJS += \
./src/arch/southern-islands/asm/arg.o \
./src/arch/southern-islands/asm/asm.o \
./src/arch/southern-islands/asm/bin-file.o \
./src/arch/southern-islands/asm/input.o 

C_DEPS += \
./src/arch/southern-islands/asm/arg.d \
./src/arch/southern-islands/asm/asm.d \
./src/arch/southern-islands/asm/bin-file.d \
./src/arch/southern-islands/asm/input.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/southern-islands/asm/%.o: ../src/arch/southern-islands/asm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


