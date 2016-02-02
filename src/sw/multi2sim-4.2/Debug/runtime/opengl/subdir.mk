################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../runtime/opengl/api.o \
../runtime/opengl/buffer.o \
../runtime/opengl/context.o \
../runtime/opengl/debug.o \
../runtime/opengl/elf-format.o \
../runtime/opengl/fog-hint.o \
../runtime/opengl/fragment.o \
../runtime/opengl/framebuffer.o \
../runtime/opengl/light.o \
../runtime/opengl/linked-list.o \
../runtime/opengl/list.o \
../runtime/opengl/matrix.o \
../runtime/opengl/mhandle.o \
../runtime/opengl/misc.o \
../runtime/opengl/opengl.o \
../runtime/opengl/pixel.o \
../runtime/opengl/program.o \
../runtime/opengl/rasterization.o \
../runtime/opengl/rectangle.o \
../runtime/opengl/render-ctrl-query.o \
../runtime/opengl/shader.o \
../runtime/opengl/special-func.o \
../runtime/opengl/state.o \
../runtime/opengl/string.o \
../runtime/opengl/sync.o \
../runtime/opengl/texture.o \
../runtime/opengl/vertex-array.o \
../runtime/opengl/vertex-spec.o \
../runtime/opengl/viewport.o 

C_SRCS += \
../runtime/opengl/api.c \
../runtime/opengl/buffer.c \
../runtime/opengl/context.c \
../runtime/opengl/debug.c \
../runtime/opengl/elf-format.c \
../runtime/opengl/fog-hint.c \
../runtime/opengl/fragment.c \
../runtime/opengl/framebuffer.c \
../runtime/opengl/light.c \
../runtime/opengl/linked-list.c \
../runtime/opengl/list.c \
../runtime/opengl/matrix.c \
../runtime/opengl/mhandle.c \
../runtime/opengl/misc.c \
../runtime/opengl/opengl.c \
../runtime/opengl/pixel.c \
../runtime/opengl/program.c \
../runtime/opengl/rasterization.c \
../runtime/opengl/rectangle.c \
../runtime/opengl/render-ctrl-query.c \
../runtime/opengl/shader.c \
../runtime/opengl/special-func.c \
../runtime/opengl/state.c \
../runtime/opengl/string.c \
../runtime/opengl/sync.c \
../runtime/opengl/texture.c \
../runtime/opengl/vertex-array.c \
../runtime/opengl/vertex-spec.c \
../runtime/opengl/viewport.c 

OBJS += \
./runtime/opengl/api.o \
./runtime/opengl/buffer.o \
./runtime/opengl/context.o \
./runtime/opengl/debug.o \
./runtime/opengl/elf-format.o \
./runtime/opengl/fog-hint.o \
./runtime/opengl/fragment.o \
./runtime/opengl/framebuffer.o \
./runtime/opengl/light.o \
./runtime/opengl/linked-list.o \
./runtime/opengl/list.o \
./runtime/opengl/matrix.o \
./runtime/opengl/mhandle.o \
./runtime/opengl/misc.o \
./runtime/opengl/opengl.o \
./runtime/opengl/pixel.o \
./runtime/opengl/program.o \
./runtime/opengl/rasterization.o \
./runtime/opengl/rectangle.o \
./runtime/opengl/render-ctrl-query.o \
./runtime/opengl/shader.o \
./runtime/opengl/special-func.o \
./runtime/opengl/state.o \
./runtime/opengl/string.o \
./runtime/opengl/sync.o \
./runtime/opengl/texture.o \
./runtime/opengl/vertex-array.o \
./runtime/opengl/vertex-spec.o \
./runtime/opengl/viewport.o 

C_DEPS += \
./runtime/opengl/api.d \
./runtime/opengl/buffer.d \
./runtime/opengl/context.d \
./runtime/opengl/debug.d \
./runtime/opengl/elf-format.d \
./runtime/opengl/fog-hint.d \
./runtime/opengl/fragment.d \
./runtime/opengl/framebuffer.d \
./runtime/opengl/light.d \
./runtime/opengl/linked-list.d \
./runtime/opengl/list.d \
./runtime/opengl/matrix.d \
./runtime/opengl/mhandle.d \
./runtime/opengl/misc.d \
./runtime/opengl/opengl.d \
./runtime/opengl/pixel.d \
./runtime/opengl/program.d \
./runtime/opengl/rasterization.d \
./runtime/opengl/rectangle.d \
./runtime/opengl/render-ctrl-query.d \
./runtime/opengl/shader.d \
./runtime/opengl/special-func.d \
./runtime/opengl/state.d \
./runtime/opengl/string.d \
./runtime/opengl/sync.d \
./runtime/opengl/texture.d \
./runtime/opengl/vertex-array.d \
./runtime/opengl/vertex-spec.d \
./runtime/opengl/viewport.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/opengl/%.o: ../runtime/opengl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


