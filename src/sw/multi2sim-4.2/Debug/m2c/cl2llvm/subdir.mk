################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/cl2llvm/cl2llvm-missing.o 

C_SRCS += \
../m2c/cl2llvm/arg.c \
../m2c/cl2llvm/array.c \
../m2c/cl2llvm/built-in-funcs.c \
../m2c/cl2llvm/cl2llvm-missing.c \
../m2c/cl2llvm/cl2llvm.c \
../m2c/cl2llvm/declarator-list.c \
../m2c/cl2llvm/enum-types.c \
../m2c/cl2llvm/for-blocks.c \
../m2c/cl2llvm/format.c \
../m2c/cl2llvm/function.c \
../m2c/cl2llvm/init.c \
../m2c/cl2llvm/lex.c \
../m2c/cl2llvm/parser.c \
../m2c/cl2llvm/symbol.c \
../m2c/cl2llvm/type.c \
../m2c/cl2llvm/val.c \
../m2c/cl2llvm/vector-ops.c \
../m2c/cl2llvm/while-blocks.c 

OBJS += \
./m2c/cl2llvm/arg.o \
./m2c/cl2llvm/array.o \
./m2c/cl2llvm/built-in-funcs.o \
./m2c/cl2llvm/cl2llvm-missing.o \
./m2c/cl2llvm/cl2llvm.o \
./m2c/cl2llvm/declarator-list.o \
./m2c/cl2llvm/enum-types.o \
./m2c/cl2llvm/for-blocks.o \
./m2c/cl2llvm/format.o \
./m2c/cl2llvm/function.o \
./m2c/cl2llvm/init.o \
./m2c/cl2llvm/lex.o \
./m2c/cl2llvm/parser.o \
./m2c/cl2llvm/symbol.o \
./m2c/cl2llvm/type.o \
./m2c/cl2llvm/val.o \
./m2c/cl2llvm/vector-ops.o \
./m2c/cl2llvm/while-blocks.o 

C_DEPS += \
./m2c/cl2llvm/arg.d \
./m2c/cl2llvm/array.d \
./m2c/cl2llvm/built-in-funcs.d \
./m2c/cl2llvm/cl2llvm-missing.d \
./m2c/cl2llvm/cl2llvm.d \
./m2c/cl2llvm/declarator-list.d \
./m2c/cl2llvm/enum-types.d \
./m2c/cl2llvm/for-blocks.d \
./m2c/cl2llvm/format.d \
./m2c/cl2llvm/function.d \
./m2c/cl2llvm/init.d \
./m2c/cl2llvm/lex.d \
./m2c/cl2llvm/parser.d \
./m2c/cl2llvm/symbol.d \
./m2c/cl2llvm/type.d \
./m2c/cl2llvm/val.d \
./m2c/cl2llvm/vector-ops.d \
./m2c/cl2llvm/while-blocks.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/cl2llvm/%.o: ../m2c/cl2llvm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


