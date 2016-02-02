################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/driver/opengl/opengl-missing.o 

C_SRCS += \
../src/driver/opengl/opengl-missing.c \
../src/driver/opengl/opengl.c \
../src/driver/opengl/si-program.c \
../src/driver/opengl/si-shader.c 

OBJS += \
./src/driver/opengl/opengl-missing.o \
./src/driver/opengl/opengl.o \
./src/driver/opengl/si-program.o \
./src/driver/opengl/si-shader.o 

C_DEPS += \
./src/driver/opengl/opengl-missing.d \
./src/driver/opengl/opengl.d \
./src/driver/opengl/si-program.d \
./src/driver/opengl/si-shader.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/opengl/%.o: ../src/driver/opengl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


