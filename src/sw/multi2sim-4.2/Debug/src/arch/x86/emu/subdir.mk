################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/arch/x86/emu/checkpoint.o \
../src/arch/x86/emu/context.o \
../src/arch/x86/emu/emu.o \
../src/arch/x86/emu/file-desc.o \
../src/arch/x86/emu/isa.o \
../src/arch/x86/emu/loader.o \
../src/arch/x86/emu/machine-ctrl.o \
../src/arch/x86/emu/machine-fp.o \
../src/arch/x86/emu/machine-rot.o \
../src/arch/x86/emu/machine-sse.o \
../src/arch/x86/emu/machine-sse2.o \
../src/arch/x86/emu/machine-sse3.o \
../src/arch/x86/emu/machine-sse4.o \
../src/arch/x86/emu/machine-std.o \
../src/arch/x86/emu/machine-str.o \
../src/arch/x86/emu/machine.o \
../src/arch/x86/emu/regs.o \
../src/arch/x86/emu/signal.o \
../src/arch/x86/emu/syscall.o \
../src/arch/x86/emu/uinst.o 

C_SRCS += \
../src/arch/x86/emu/checkpoint.c \
../src/arch/x86/emu/context.c \
../src/arch/x86/emu/emu.c \
../src/arch/x86/emu/file-desc.c \
../src/arch/x86/emu/isa.c \
../src/arch/x86/emu/loader.c \
../src/arch/x86/emu/machine-ctrl.c \
../src/arch/x86/emu/machine-fp.c \
../src/arch/x86/emu/machine-rot.c \
../src/arch/x86/emu/machine-sse.c \
../src/arch/x86/emu/machine-sse2.c \
../src/arch/x86/emu/machine-sse3.c \
../src/arch/x86/emu/machine-sse4.c \
../src/arch/x86/emu/machine-std.c \
../src/arch/x86/emu/machine-str.c \
../src/arch/x86/emu/machine.c \
../src/arch/x86/emu/regs.c \
../src/arch/x86/emu/signal.c \
../src/arch/x86/emu/syscall.c \
../src/arch/x86/emu/uinst.c 

OBJS += \
./src/arch/x86/emu/checkpoint.o \
./src/arch/x86/emu/context.o \
./src/arch/x86/emu/emu.o \
./src/arch/x86/emu/file-desc.o \
./src/arch/x86/emu/isa.o \
./src/arch/x86/emu/loader.o \
./src/arch/x86/emu/machine-ctrl.o \
./src/arch/x86/emu/machine-fp.o \
./src/arch/x86/emu/machine-rot.o \
./src/arch/x86/emu/machine-sse.o \
./src/arch/x86/emu/machine-sse2.o \
./src/arch/x86/emu/machine-sse3.o \
./src/arch/x86/emu/machine-sse4.o \
./src/arch/x86/emu/machine-std.o \
./src/arch/x86/emu/machine-str.o \
./src/arch/x86/emu/machine.o \
./src/arch/x86/emu/regs.o \
./src/arch/x86/emu/signal.o \
./src/arch/x86/emu/syscall.o \
./src/arch/x86/emu/uinst.o 

C_DEPS += \
./src/arch/x86/emu/checkpoint.d \
./src/arch/x86/emu/context.d \
./src/arch/x86/emu/emu.d \
./src/arch/x86/emu/file-desc.d \
./src/arch/x86/emu/isa.d \
./src/arch/x86/emu/loader.d \
./src/arch/x86/emu/machine-ctrl.d \
./src/arch/x86/emu/machine-fp.d \
./src/arch/x86/emu/machine-rot.d \
./src/arch/x86/emu/machine-sse.d \
./src/arch/x86/emu/machine-sse2.d \
./src/arch/x86/emu/machine-sse3.d \
./src/arch/x86/emu/machine-sse4.d \
./src/arch/x86/emu/machine-std.d \
./src/arch/x86/emu/machine-str.d \
./src/arch/x86/emu/machine.d \
./src/arch/x86/emu/regs.d \
./src/arch/x86/emu/signal.d \
./src/arch/x86/emu/syscall.d \
./src/arch/x86/emu/uinst.d 


# Each subdirectory must supply rules for building sources it contributes
src/arch/x86/emu/%.o: ../src/arch/x86/emu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


