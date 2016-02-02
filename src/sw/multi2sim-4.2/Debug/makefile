################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/visual/x86/subdir.mk
-include src/visual/southern-islands/subdir.mk
-include src/visual/memory/subdir.mk
-include src/visual/evergreen/subdir.mk
-include src/visual/common/subdir.mk
-include src/network/subdir.mk
-include src/mem-system/subdir.mk
-include src/subdir.mk
-include src/lib/util/subdir.mk
-include src/lib/mhandle/subdir.mk
-include src/lib/esim/subdir.mk
-include src/driver/opengl/subdir.mk
-include src/driver/opencl-old/evergreen/subdir.mk
-include src/driver/opencl/subdir.mk
-include src/driver/glut/subdir.mk
-include src/driver/glu/subdir.mk
-include src/driver/glew/subdir.mk
-include src/driver/cuda/subdir.mk
-include src/dram/subdir.mk
-include src/arch/x86/timing/subdir.mk
-include src/arch/x86/emu/subdir.mk
-include src/arch/x86/asm/subdir.mk
-include src/arch/southern-islands/timing/subdir.mk
-include src/arch/southern-islands/emu/subdir.mk
-include src/arch/southern-islands/asm/subdir.mk
-include src/arch/mips/timing/subdir.mk
-include src/arch/mips/emu/subdir.mk
-include src/arch/mips/asm/subdir.mk
-include src/arch/kepler/asm/subdir.mk
-include src/arch/fermi/timing/subdir.mk
-include src/arch/fermi/emu/subdir.mk
-include src/arch/fermi/asm/subdir.mk
-include src/arch/evergreen/timing/subdir.mk
-include src/arch/evergreen/emu/subdir.mk
-include src/arch/evergreen/asm/subdir.mk
-include src/arch/common/subdir.mk
-include src/arch/arm/timing/subdir.mk
-include src/arch/arm/emu/subdir.mk
-include src/arch/arm/asm/subdir.mk
-include samples/x86/subdir.mk
-include samples/mips/subdir.mk
-include samples/arm/subdir.mk
-include runtime/opengl/subdir.mk
-include runtime/opengl/.libs/subdir.mk
-include runtime/opencl-old/subdir.mk
-include runtime/opencl-old/.libs/subdir.mk
-include runtime/opencl/subdir.mk
-include runtime/opencl/.libs/subdir.mk
-include runtime/glut/subdir.mk
-include runtime/glut/.libs/subdir.mk
-include runtime/glu/subdir.mk
-include runtime/glu/.libs/subdir.mk
-include runtime/glew/subdir.mk
-include runtime/glew/.libs/subdir.mk
-include runtime/cuda/subdir.mk
-include runtime/cuda/.libs/subdir.mk
-include m2c/si2bin/subdir.mk
-include m2c/subdir.mk
-include m2c/llvm2si/subdir.mk
-include m2c/gl/subdir.mk
-include m2c/frm2bin/subdir.mk
-include m2c/common/subdir.mk
-include m2c/cl2llvm/subdir.mk
-include m2c/amd/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: M2S-4.2

# Tool invocations
M2S-4.2: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"M2S-4.2" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) M2S-4.2
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
