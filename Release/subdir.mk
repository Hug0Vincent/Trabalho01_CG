################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJ_SRCS += \
../teste.obj \
../teste2.obj 

CPP_SRCS += \
../helloworld_gtk.cpp \
../helloworld_gtkmm.cpp \
../subject_controller_test.cpp \
../test_array_initicialization.cpp \
../test_coordinate_initicialization.cpp \
../test_template_initicialization.cpp \
../timestamp_example.cpp 

OBJS += \
./helloworld_gtk.o \
./helloworld_gtkmm.o \
./subject_controller_test.o \
./test_array_initicialization.o \
./test_coordinate_initicialization.o \
./test_template_initicialization.o \
./timestamp_example.o 

CPP_DEPS += \
./helloworld_gtk.d \
./helloworld_gtkmm.d \
./subject_controller_test.d \
./test_array_initicialization.d \
./test_coordinate_initicialization.d \
./test_template_initicialization.d \
./timestamp_example.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


