################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/ShowIncludes/main.c 

C_DEPS += \
./Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/ShowIncludes/main.d 

OBJS += \
./Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/ShowIncludes/main.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/ShowIncludes/%.o: ../Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/ShowIncludes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4500_F100x768 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4500_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.
