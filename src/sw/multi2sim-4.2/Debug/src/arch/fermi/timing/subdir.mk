################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/fermi/timing/branch-unit.o \
../src/arch/fermi/timing/calc.o \
../src/arch/fermi/timing/cycle-interval-report.o \
../src/arch/fermi/timing/gpu.o \
../src/arch/fermi/timing/lds-unit.o \
../src/arch/fermi/timing/mem-config.o \
../src/arch/fermi/timing/simd-unit.o \
../src/arch/fermi/timing/sm.o \
../src/arch/fermi/timing/uop.o \
../src/arch/fermi/timing/vector-mem-unit.o \
../src/arch/fermi/timing/warp-inst-queue.o 

C_SRCS += \
../src/arch/fermi/timing/branch-unit.c \
../src/arch/fermi/timing/calc.c \
../src/arch/fermi/timing/cycle-interval-report.c \
../src/arch/fermi/timing/gpu.c \
../src/arch/fermi/timing/lds-unit.c \
../src/arch/fermi/timing/mem-config.c \
../src/arch/fermi/timing/simd-unit.c \
../src/arch/fermi/timing/sm.c \
../src/arch/fermi/timing/uop.c \
../src/arch/fermi/timing/vector-mem-unit.c \
../src/arch/fermi/timing/warp-inst-queue.c 

OBJS += \
./src/arch/fermi/timing/branch-unit.o \
./src/arch/fermi/timing/calc.o \
./src/arch/fermi/timing/cycle-interval-report.o \
./src/arch/fermi/timing/gpu.o \
./src/arch/fermi/timing/lds-unit.o \
./src/arch/fermi/timing/mem-config.o \
./src/arch/fermi/timing/simd-unit.o \
./src/arch/fermi/timing/sm.o \
./src/arch/fermi/timing/uop.o \
./src/arch/fermi/timing/vector-mem-unit.o \
./src/arch/fermi/timing/warp-inst-queue.o 

C_DEPS += \
./src/arch/fermi/timing/branch-unit.d \
./src/arch/fermi/timing/calc.d \
./src/arch/fermi/timing/cycle-interval-report.d \
./src/arch/fermi/timing/gpu.d \
./src/arch/fermi/timing/lds-unit.d \
./src/arch/fermi/timing/mem-config.d \
./src/arch/fermi/timing/simd-unit.d \
./src/arch/fermi/timing/sm.d \
./src/arch/fermi/timing/uop.d \
./src/arch/fermi/timing/vector-mem-unit.d \
./src/arch/fermi/timing/warp-inst-queue.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/fermi/timing/%.o: ../src/arch/fermi/timing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


