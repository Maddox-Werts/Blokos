# THIS IS THE MAKE FILE FOR TURNING
# ALL C FILES INTO BINARIES

# VARIABLES
LIBS = -lsdl2main -lsdl2

# COMPILING
all: compile link clean

compile:
	gcc -c -I inc src/game/*.c
	gcc -c -I inc src/app/*.c
	gcc -c -I inc src/*.c

link:
	gcc *.o -L lib $(LIBS) -o bin/blokos

clean:
	rm *.o