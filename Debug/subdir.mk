################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../M_TIMER_program.c \
../app.c \
../external_interrupt_program.c \
../mdio_program.c \
../mgie_program.c \
../seven_seg_program.c \
../timer.c 

OBJS += \
./M_TIMER_program.o \
./app.o \
./external_interrupt_program.o \
./mdio_program.o \
./mgie_program.o \
./seven_seg_program.o \
./timer.o 

C_DEPS += \
./M_TIMER_program.d \
./app.d \
./external_interrupt_program.d \
./mdio_program.d \
./mgie_program.d \
./seven_seg_program.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


