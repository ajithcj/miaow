################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/lib/util/bin-config.o \
../src/lib/util/bit-map.o \
../src/lib/util/buffer.o \
../src/lib/util/class.o \
../src/lib/util/config.o \
../src/lib/util/debug.o \
../src/lib/util/elf-encode.o \
../src/lib/util/elf-format.o \
../src/lib/util/file.o \
../src/lib/util/hash-table.o \
../src/lib/util/heap.o \
../src/lib/util/linked-list.o \
../src/lib/util/list.o \
../src/lib/util/matrix.o \
../src/lib/util/misc.o \
../src/lib/util/repos.o \
../src/lib/util/string.o \
../src/lib/util/timer.o 

C_SRCS += \
../src/lib/util/bin-config.c \
../src/lib/util/bit-map.c \
../src/lib/util/buffer.c \
../src/lib/util/class.c \
../src/lib/util/config.c \
../src/lib/util/debug.c \
../src/lib/util/elf-encode.c \
../src/lib/util/elf-format.c \
../src/lib/util/file.c \
../src/lib/util/hash-table.c \
../src/lib/util/heap.c \
../src/lib/util/linked-list.c \
../src/lib/util/list.c \
../src/lib/util/matrix.c \
../src/lib/util/misc.c \
../src/lib/util/repos.c \
../src/lib/util/string.c \
../src/lib/util/timer.c 

OBJS += \
./src/lib/util/bin-config.o \
./src/lib/util/bit-map.o \
./src/lib/util/buffer.o \
./src/lib/util/class.o \
./src/lib/util/config.o \
./src/lib/util/debug.o \
./src/lib/util/elf-encode.o \
./src/lib/util/elf-format.o \
./src/lib/util/file.o \
./src/lib/util/hash-table.o \
./src/lib/util/heap.o \
./src/lib/util/linked-list.o \
./src/lib/util/list.o \
./src/lib/util/matrix.o \
./src/lib/util/misc.o \
./src/lib/util/repos.o \
./src/lib/util/string.o \
./src/lib/util/timer.o 

C_DEPS += \
./src/lib/util/bin-config.d \
./src/lib/util/bit-map.d \
./src/lib/util/buffer.d \
./src/lib/util/class.d \
./src/lib/util/config.d \
./src/lib/util/debug.d \
./src/lib/util/elf-encode.d \
./src/lib/util/elf-format.d \
./src/lib/util/file.d \
./src/lib/util/hash-table.d \
./src/lib/util/heap.d \
./src/lib/util/linked-list.d \
./src/lib/util/list.d \
./src/lib/util/matrix.d \
./src/lib/util/misc.d \
./src/lib/util/repos.d \
./src/lib/util/string.d \
./src/lib/util/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/util/%.o: ../src/lib/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


