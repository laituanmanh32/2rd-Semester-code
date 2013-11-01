################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/HCZHeader.o \
../src/HuffmanCode.o \
../src/Reader.o \
../src/Writer.o \
../src/main.o 

CPP_SRCS += \
../src/HCZHeader.cpp \
../src/HuffmanCode.cpp \
../src/Main.cpp \
../src/Reader.cpp \
../src/Writer.cpp \
../src/hr_time.cpp 

OBJS += \
./src/HCZHeader.o \
./src/HuffmanCode.o \
./src/Main.o \
./src/Reader.o \
./src/Writer.o \
./src/hr_time.o 

CPP_DEPS += \
./src/HCZHeader.d \
./src/HuffmanCode.d \
./src/Main.d \
./src/Reader.d \
./src/Writer.d \
./src/hr_time.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


