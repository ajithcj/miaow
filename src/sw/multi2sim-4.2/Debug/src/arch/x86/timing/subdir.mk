################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/x86/timing/bpred.o \
../src/arch/x86/timing/commit.o \
../src/arch/x86/timing/core.o \
../src/arch/x86/timing/cpu.o \
../src/arch/x86/timing/decode.o \
../src/arch/x86/timing/dispatch.o \
../src/arch/x86/timing/event-queue.o \
../src/arch/x86/timing/fetch-queue.o \
../src/arch/x86/timing/fetch.o \
../src/arch/x86/timing/fu.o \
../src/arch/x86/timing/inst-queue.o \
../src/arch/x86/timing/issue.o \
../src/arch/x86/timing/load-store-queue.o \
../src/arch/x86/timing/mem-config.o \
../src/arch/x86/timing/recover.o \
../src/arch/x86/timing/reg-file.o \
../src/arch/x86/timing/rob.o \
../src/arch/x86/timing/sched.o \
../src/arch/x86/timing/thread.o \
../src/arch/x86/timing/trace-cache.o \
../src/arch/x86/timing/uop-queue.o \
../src/arch/x86/timing/uop.o \
../src/arch/x86/timing/writeback.o 

C_SRCS += \
../src/arch/x86/timing/bpred.c \
../src/arch/x86/timing/commit.c \
../src/arch/x86/timing/core.c \
../src/arch/x86/timing/cpu.c \
../src/arch/x86/timing/decode.c \
../src/arch/x86/timing/dispatch.c \
../src/arch/x86/timing/event-queue.c \
../src/arch/x86/timing/fetch-queue.c \
../src/arch/x86/timing/fetch.c \
../src/arch/x86/timing/fu.c \
../src/arch/x86/timing/inst-queue.c \
../src/arch/x86/timing/issue.c \
../src/arch/x86/timing/load-store-queue.c \
../src/arch/x86/timing/mem-config.c \
../src/arch/x86/timing/recover.c \
../src/arch/x86/timing/reg-file.c \
../src/arch/x86/timing/rob.c \
../src/arch/x86/timing/sched.c \
../src/arch/x86/timing/thread.c \
../src/arch/x86/timing/trace-cache.c \
../src/arch/x86/timing/uop-queue.c \
../src/arch/x86/timing/uop.c \
../src/arch/x86/timing/writeback.c 

OBJS += \
./src/arch/x86/timing/bpred.o \
./src/arch/x86/timing/commit.o \
./src/arch/x86/timing/core.o \
./src/arch/x86/timing/cpu.o \
./src/arch/x86/timing/decode.o \
./src/arch/x86/timing/dispatch.o \
./src/arch/x86/timing/event-queue.o \
./src/arch/x86/timing/fetch-queue.o \
./src/arch/x86/timing/fetch.o \
./src/arch/x86/timing/fu.o \
./src/arch/x86/timing/inst-queue.o \
./src/arch/x86/timing/issue.o \
./src/arch/x86/timing/load-store-queue.o \
./src/arch/x86/timing/mem-config.o \
./src/arch/x86/timing/recover.o \
./src/arch/x86/timing/reg-file.o \
./src/arch/x86/timing/rob.o \
./src/arch/x86/timing/sched.o \
./src/arch/x86/timing/thread.o \
./src/arch/x86/timing/trace-cache.o \
./src/arch/x86/timing/uop-queue.o \
./src/arch/x86/timing/uop.o \
./src/arch/x86/timing/writeback.o 

C_DEPS += \
./src/arch/x86/timing/bpred.d \
./src/arch/x86/timing/commit.d \
./src/arch/x86/timing/core.d \
./src/arch/x86/timing/cpu.d \
./src/arch/x86/timing/decode.d \
./src/arch/x86/timing/dispatch.d \
./src/arch/x86/timing/event-queue.d \
./src/arch/x86/timing/fetch-queue.d \
./src/arch/x86/timing/fetch.d \
./src/arch/x86/timing/fu.d \
./src/arch/x86/timing/inst-queue.d \
./src/arch/x86/timing/issue.d \
./src/arch/x86/timing/load-store-queue.d \
./src/arch/x86/timing/mem-config.d \
./src/arch/x86/timing/recover.d \
./src/arch/x86/timing/reg-file.d \
./src/arch/x86/timing/rob.d \
./src/arch/x86/timing/sched.d \
./src/arch/x86/timing/thread.d \
./src/arch/x86/timing/trace-cache.d \
./src/arch/x86/timing/uop-queue.d \
./src/arch/x86/timing/uop.d \
./src/arch/x86/timing/writeback.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/x86/timing/%.o: ../src/arch/x86/timing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


