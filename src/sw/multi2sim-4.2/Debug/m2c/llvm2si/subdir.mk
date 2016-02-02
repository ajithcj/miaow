################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/llvm2si/llvm2si-missing.o 

C_SRCS += \
../m2c/llvm2si/basic-block.c \
../m2c/llvm2si/function.c \
../m2c/llvm2si/llvm2si-missing.c \
../m2c/llvm2si/llvm2si.c \
../m2c/llvm2si/phi.c \
../m2c/llvm2si/symbol-table.c \
../m2c/llvm2si/symbol.c 

OBJS += \
./m2c/llvm2si/basic-block.o \
./m2c/llvm2si/function.o \
./m2c/llvm2si/llvm2si-missing.o \
./m2c/llvm2si/llvm2si.o \
./m2c/llvm2si/phi.o \
./m2c/llvm2si/symbol-table.o \
./m2c/llvm2si/symbol.o 

C_DEPS += \
./m2c/llvm2si/basic-block.d \
./m2c/llvm2si/function.d \
./m2c/llvm2si/llvm2si-missing.d \
./m2c/llvm2si/llvm2si.d \
./m2c/llvm2si/phi.d \
./m2c/llvm2si/symbol-table.d \
./m2c/llvm2si/symbol.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/llvm2si/%.o: ../m2c/llvm2si/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


