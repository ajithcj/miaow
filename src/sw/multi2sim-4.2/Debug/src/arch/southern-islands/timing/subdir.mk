################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/southern-islands/timing/branch-unit.o \
../src/arch/southern-islands/timing/calc.o \
../src/arch/southern-islands/timing/compute-unit.o \
../src/arch/southern-islands/timing/cycle-interval-report.o \
../src/arch/southern-islands/timing/gpu.o \
../src/arch/southern-islands/timing/lds-unit.o \
../src/arch/southern-islands/timing/mem-config.o \
../src/arch/southern-islands/timing/scalar-unit.o \
../src/arch/southern-islands/timing/simd-unit.o \
../src/arch/southern-islands/timing/uop.o \
../src/arch/southern-islands/timing/vector-mem-unit.o \
../src/arch/southern-islands/timing/wavefront-pool.o 

C_SRCS += \
../src/arch/southern-islands/timing/branch-unit.c \
../src/arch/southern-islands/timing/calc.c \
../src/arch/southern-islands/timing/compute-unit.c \
../src/arch/southern-islands/timing/cycle-interval-report.c \
../src/arch/southern-islands/timing/gpu.c \
../src/arch/southern-islands/timing/lds-unit.c \
../src/arch/southern-islands/timing/mem-config.c \
../src/arch/southern-islands/timing/scalar-unit.c \
../src/arch/southern-islands/timing/simd-unit.c \
../src/arch/southern-islands/timing/uop.c \
../src/arch/southern-islands/timing/vector-mem-unit.c \
../src/arch/southern-islands/timing/wavefront-pool.c 

OBJS += \
./src/arch/southern-islands/timing/branch-unit.o \
./src/arch/southern-islands/timing/calc.o \
./src/arch/southern-islands/timing/compute-unit.o \
./src/arch/southern-islands/timing/cycle-interval-report.o \
./src/arch/southern-islands/timing/gpu.o \
./src/arch/southern-islands/timing/lds-unit.o \
./src/arch/southern-islands/timing/mem-config.o \
./src/arch/southern-islands/timing/scalar-unit.o \
./src/arch/southern-islands/timing/simd-unit.o \
./src/arch/southern-islands/timing/uop.o \
./src/arch/southern-islands/timing/vector-mem-unit.o \
./src/arch/southern-islands/timing/wavefront-pool.o 

C_DEPS += \
./src/arch/southern-islands/timing/branch-unit.d \
./src/arch/southern-islands/timing/calc.d \
./src/arch/southern-islands/timing/compute-unit.d \
./src/arch/southern-islands/timing/cycle-interval-report.d \
./src/arch/southern-islands/timing/gpu.d \
./src/arch/southern-islands/timing/lds-unit.d \
./src/arch/southern-islands/timing/mem-config.d \
./src/arch/southern-islands/timing/scalar-unit.d \
./src/arch/southern-islands/timing/simd-unit.d \
./src/arch/southern-islands/timing/uop.d \
./src/arch/southern-islands/timing/vector-mem-unit.d \
./src/arch/southern-islands/timing/wavefront-pool.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/southern-islands/timing/%.o: ../src/arch/southern-islands/timing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


