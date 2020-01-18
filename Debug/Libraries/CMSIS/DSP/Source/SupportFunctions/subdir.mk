################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.c 

C_DEPS += \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d 

OBJS += \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./Libraries/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/DSP/Source/SupportFunctions/%.o: ../Libraries/CMSIS/DSP/Source/SupportFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4500_F100x768 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/DSP/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4500_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

