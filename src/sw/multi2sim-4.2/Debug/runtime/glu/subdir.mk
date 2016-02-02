################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/glu/api.o \
../runtime/glu/debug.o \
../runtime/glu/list.o \
../runtime/glu/mhandle.o \
../runtime/glu/misc.o \
../runtime/glu/string.o 

C_SRCS += \
../runtime/glu/api.c \
../runtime/glu/debug.c \
../runtime/glu/list.c \
../runtime/glu/mhandle.c \
../runtime/glu/misc.c \
../runtime/glu/string.c 

OBJS += \
./runtime/glu/api.o \
./runtime/glu/debug.o \
./runtime/glu/list.o \
./runtime/glu/mhandle.o \
./runtime/glu/misc.o \
./runtime/glu/string.o 

C_DEPS += \
./runtime/glu/api.d \
./runtime/glu/debug.d \
./runtime/glu/list.d \
./runtime/glu/mhandle.d \
./runtime/glu/misc.d \
./runtime/glu/string.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/glu/%.o: ../runtime/glu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


