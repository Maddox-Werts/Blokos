# THIS IS THE MAKE FILE FOR TURNING
# ALL C FILES INTO BINARIES

# VARIABLES
LIBS = -lsdl2main -lsdl_ttf -lsdl2
PLATFORM = APPLE

# COMPILING
all: CLS compile link install clean run

CLS:
	clear

compile:
	gcc -c -I inc src/gme/*.c
	gcc -c -I inc src/app/*.c
	gcc -c -I inc src/scn/*.c
	gcc -c -I inc src/*.c

link:
	gcc *.o -L lib $(LIBS) -o bin/$(PLATFORM)/blokos

install:
	cp res bin/$(PLATFORM)/res

clean:
	rm *.o

run:
	./bin/$(PLATFORM)/blokos