all: emulator_build

emulator_build: emulator.cpp
	g++ -g -I./include emulator.cpp -o emulator
