################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/si2bin/arg.o \
../m2c/si2bin/data.o \
../m2c/si2bin/id.o \
../m2c/si2bin/inner-bin.o \
../m2c/si2bin/inst-info.o \
../m2c/si2bin/inst.o \
../m2c/si2bin/lex.o \
../m2c/si2bin/metadata.o \
../m2c/si2bin/outer-bin.o \
../m2c/si2bin/parser.o \
../m2c/si2bin/si2bin.o \
../m2c/si2bin/symbol.o \
../m2c/si2bin/task.o \
../m2c/si2bin/token.o 

C_SRCS += \
../m2c/si2bin/arg.c \
../m2c/si2bin/data.c \
../m2c/si2bin/id.c \
../m2c/si2bin/inner-bin.c \
../m2c/si2bin/inst-info.c \
../m2c/si2bin/inst.c \
../m2c/si2bin/lex.c \
../m2c/si2bin/metadata.c \
../m2c/si2bin/outer-bin.c \
../m2c/si2bin/parser.c \
../m2c/si2bin/si2bin-missing.c \
../m2c/si2bin/si2bin.c \
../m2c/si2bin/symbol.c \
../m2c/si2bin/task.c \
../m2c/si2bin/token.c 

OBJS += \
./m2c/si2bin/arg.o \
./m2c/si2bin/data.o \
./m2c/si2bin/id.o \
./m2c/si2bin/inner-bin.o \
./m2c/si2bin/inst-info.o \
./m2c/si2bin/inst.o \
./m2c/si2bin/lex.o \
./m2c/si2bin/metadata.o \
./m2c/si2bin/outer-bin.o \
./m2c/si2bin/parser.o \
./m2c/si2bin/si2bin-missing.o \
./m2c/si2bin/si2bin.o \
./m2c/si2bin/symbol.o \
./m2c/si2bin/task.o \
./m2c/si2bin/token.o 

C_DEPS += \
./m2c/si2bin/arg.d \
./m2c/si2bin/data.d \
./m2c/si2bin/id.d \
./m2c/si2bin/inner-bin.d \
./m2c/si2bin/inst-info.d \
./m2c/si2bin/inst.d \
./m2c/si2bin/lex.d \
./m2c/si2bin/metadata.d \
./m2c/si2bin/outer-bin.d \
./m2c/si2bin/parser.d \
./m2c/si2bin/si2bin-missing.d \
./m2c/si2bin/si2bin.d \
./m2c/si2bin/symbol.d \
./m2c/si2bin/task.d \
./m2c/si2bin/token.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/si2bin/%.o: ../m2c/si2bin/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


