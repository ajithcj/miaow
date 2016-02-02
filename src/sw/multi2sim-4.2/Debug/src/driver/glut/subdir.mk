################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/glut/glut-missing.o 

C_SRCS += \
../src/driver/glut/frame-buffer.c \
../src/driver/glut/glut-missing.c \
../src/driver/glut/glut.c 

OBJS += \
./src/driver/glut/frame-buffer.o \
./src/driver/glut/glut-missing.o \
./src/driver/glut/glut.o 

C_DEPS += \
./src/driver/glut/frame-buffer.d \
./src/driver/glut/glut-missing.d \
./src/driver/glut/glut.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/glut/%.o: ../src/driver/glut/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


