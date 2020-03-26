# makefile
COMMON_OBJECTS =
CPU		= MSP430G2553
CFLAGS		= -mmcu=${CPU} -I./h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-eld-as

all: states.elf

states.elf: ${COMMON_OBJECTS} buttonMain.o stateMachines.o switches.o buzzer.o led.o p1_interrupt_handler.o buttonMain.o ./lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: states.elf
	msp430loader.sh states.elf

clean:
	rm -f *.o *.elf *~
