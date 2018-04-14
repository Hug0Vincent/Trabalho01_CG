################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ChooseFileWindow.cpp \
../src/RwObjectService.cpp \
../src/addobject.cpp \
../src/addtransformation.cpp \
../src/beziercurve.cpp \
../src/coordinate.cpp \
../src/debugger.cpp \
../src/displayfile.cpp \
../src/drawableobject.cpp \
../src/drawingarea.cpp \
../src/line.cpp \
../src/main.cpp \
../src/mainwindow.cpp \
../src/point.cpp \
../src/polygon.cpp \
../src/transformation.cpp \
../src/transformationdata.cpp \
../src/vector.cpp \
../src/viewwindow.cpp \
../src/world.cpp 

OBJS += \
./src/ChooseFileWindow.o \
./src/RwObjectService.o \
./src/addobject.o \
./src/addtransformation.o \
./src/beziercurve.o \
./src/coordinate.o \
./src/debugger.o \
./src/displayfile.o \
./src/drawableobject.o \
./src/drawingarea.o \
./src/line.o \
./src/main.o \
./src/mainwindow.o \
./src/point.o \
./src/polygon.o \
./src/transformation.o \
./src/transformationdata.o \
./src/vector.o \
./src/viewwindow.o \
./src/world.o 

CPP_DEPS += \
./src/ChooseFileWindow.d \
./src/RwObjectService.d \
./src/addobject.d \
./src/addtransformation.d \
./src/beziercurve.d \
./src/coordinate.d \
./src/debugger.d \
./src/displayfile.d \
./src/drawableobject.d \
./src/drawingarea.d \
./src/line.d \
./src/main.d \
./src/mainwindow.d \
./src/point.d \
./src/polygon.d \
./src/transformation.d \
./src/transformationdata.d \
./src/vector.d \
./src/viewwindow.d \
./src/world.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


