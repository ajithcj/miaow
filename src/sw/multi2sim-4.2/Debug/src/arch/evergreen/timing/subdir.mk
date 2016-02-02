################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/evergreen/timing/alu-engine.o \
../src/arch/evergreen/timing/calc.o \
../src/arch/evergreen/timing/cf-engine.o \
../src/arch/evergreen/timing/compute-unit.o \
../src/arch/evergreen/timing/cycle-interval-report.o \
../src/arch/evergreen/timing/faults.o \
../src/arch/evergreen/timing/gpu.o \
../src/arch/evergreen/timing/instruction-interval-report.o \
../src/arch/evergreen/timing/mem-config.o \
../src/arch/evergreen/timing/sched.o \
../src/arch/evergreen/timing/tex-engine.o \
../src/arch/evergreen/timing/uop.o 

C_SRCS += \
../src/arch/evergreen/timing/alu-engine.c \
../src/arch/evergreen/timing/calc.c \
../src/arch/evergreen/timing/cf-engine.c \
../src/arch/evergreen/timing/compute-unit.c \
../src/arch/evergreen/timing/cycle-interval-report.c \
../src/arch/evergreen/timing/faults.c \
../src/arch/evergreen/timing/gpu.c \
../src/arch/evergreen/timing/instruction-interval-report.c \
../src/arch/evergreen/timing/mem-config.c \
../src/arch/evergreen/timing/sched.c \
../src/arch/evergreen/timing/tex-engine.c \
../src/arch/evergreen/timing/uop.c 

OBJS += \
./src/arch/evergreen/timing/alu-engine.o \
./src/arch/evergreen/timing/calc.o \
./src/arch/evergreen/timing/cf-engine.o \
./src/arch/evergreen/timing/compute-unit.o \
./src/arch/evergreen/timing/cycle-interval-report.o \
./src/arch/evergreen/timing/faults.o \
./src/arch/evergreen/timing/gpu.o \
./src/arch/evergreen/timing/instruction-interval-report.o \
./src/arch/evergreen/timing/mem-config.o \
./src/arch/evergreen/timing/sched.o \
./src/arch/evergreen/timing/tex-engine.o \
./src/arch/evergreen/timing/uop.o 

C_DEPS += \
./src/arch/evergreen/timing/alu-engine.d \
./src/arch/evergreen/timing/calc.d \
./src/arch/evergreen/timing/cf-engine.d \
./src/arch/evergreen/timing/compute-unit.d \
./src/arch/evergreen/timing/cycle-interval-report.d \
./src/arch/evergreen/timing/faults.d \
./src/arch/evergreen/timing/gpu.d \
./src/arch/evergreen/timing/instruction-interval-report.d \
./src/arch/evergreen/timing/mem-config.d \
./src/arch/evergreen/timing/sched.d \
./src/arch/evergreen/timing/tex-engine.d \
./src/arch/evergreen/timing/uop.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/evergreen/timing/%.o: ../src/arch/evergreen/timing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


