FQBN := arduino:avr:nano:cpu=atmega328old
PORT := /dev/cu.usbserial-12AP0972
CC := arduino-cli
BAUD := 9600

all: compile

compile:
	$(CC) compile --fqbn $(FQBN)

upload: compile
	$(CC) upload --fqbn $(FQBN) --port $(PORT)

serial:
	$(CC) monitor --port $(PORT) --fqbn $(FQBN) --config ${BAUD}

