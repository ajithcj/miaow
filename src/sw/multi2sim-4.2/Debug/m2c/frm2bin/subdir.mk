################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/frm2bin/arg.o \
../m2c/frm2bin/frm2bin.o \
../m2c/frm2bin/id.o \
../m2c/frm2bin/inner-bin.o \
../m2c/frm2bin/inst-info.o \
../m2c/frm2bin/inst.o \
../m2c/frm2bin/lex.o \
../m2c/frm2bin/outer-bin.o \
../m2c/frm2bin/parser.o \
../m2c/frm2bin/symbol.o \
../m2c/frm2bin/token.o 

C_SRCS += \
../m2c/frm2bin/arg.c \
../m2c/frm2bin/frm2bin-missing.c \
../m2c/frm2bin/frm2bin.c \
../m2c/frm2bin/id.c \
../m2c/frm2bin/inner-bin.c \
../m2c/frm2bin/inst-info.c \
../m2c/frm2bin/inst.c \
../m2c/frm2bin/lex.c \
../m2c/frm2bin/outer-bin.c \
../m2c/frm2bin/parser.c \
../m2c/frm2bin/symbol.c \
../m2c/frm2bin/token.c 

OBJS += \
./m2c/frm2bin/arg.o \
./m2c/frm2bin/frm2bin-missing.o \
./m2c/frm2bin/frm2bin.o \
./m2c/frm2bin/id.o \
./m2c/frm2bin/inner-bin.o \
./m2c/frm2bin/inst-info.o \
./m2c/frm2bin/inst.o \
./m2c/frm2bin/lex.o \
./m2c/frm2bin/outer-bin.o \
./m2c/frm2bin/parser.o \
./m2c/frm2bin/symbol.o \
./m2c/frm2bin/token.o 

C_DEPS += \
./m2c/frm2bin/arg.d \
./m2c/frm2bin/frm2bin-missing.d \
./m2c/frm2bin/frm2bin.d \
./m2c/frm2bin/id.d \
./m2c/frm2bin/inner-bin.d \
./m2c/frm2bin/inst-info.d \
./m2c/frm2bin/inst.d \
./m2c/frm2bin/lex.d \
./m2c/frm2bin/outer-bin.d \
./m2c/frm2bin/parser.d \
./m2c/frm2bin/symbol.d \
./m2c/frm2bin/token.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/frm2bin/%.o: ../m2c/frm2bin/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


