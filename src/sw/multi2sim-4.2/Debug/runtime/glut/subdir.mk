################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/glut/api.o \
../runtime/glut/debug.o \
../runtime/glut/list.o \
../runtime/glut/mhandle.o \
../runtime/glut/window.o 

C_SRCS += \
../runtime/glut/api.c \
../runtime/glut/debug.c \
../runtime/glut/list.c \
../runtime/glut/mhandle.c \
../runtime/glut/window.c 

OBJS += \
./runtime/glut/api.o \
./runtime/glut/debug.o \
./runtime/glut/list.o \
./runtime/glut/mhandle.o \
./runtime/glut/window.o 

C_DEPS += \
./runtime/glut/api.d \
./runtime/glut/debug.d \
./runtime/glut/list.d \
./runtime/glut/mhandle.d \
./runtime/glut/window.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/glut/%.o: ../runtime/glut/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


