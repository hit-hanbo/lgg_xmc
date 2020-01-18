################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/3.15.19101501-MSVC_2/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/3.15.19101501-MSVC_2/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/3.15.19101501-MSVC_2/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/3.15.19101501-MSVC_2/CompilerIdCXX/%.o: ../Libraries/CMSIS/DSP/Source/out/build/x64-Debug/CMakeFiles/3.15.19101501-MSVC_2/CompilerIdCXX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C++ Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-g++" -MMD -MT "$@" -DXMC4500_F100x768 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4500_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -fno-exceptions -fno-rtti -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

