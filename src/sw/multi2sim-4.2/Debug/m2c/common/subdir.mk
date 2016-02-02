################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../m2c/common/basic-block.o \
../m2c/common/ctree.o \
../m2c/common/node.o 

C_SRCS += \
../m2c/common/basic-block.c \
../m2c/common/ctree.c \
../m2c/common/node.c 

OBJS += \
./m2c/common/basic-block.o \
./m2c/common/ctree.o \
./m2c/common/node.o 

C_DEPS += \
./m2c/common/basic-block.d \
./m2c/common/ctree.d \
./m2c/common/node.d 


# Each subdirectory must supply rules for building sources it contributes
m2c/common/%.o: ../m2c/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


