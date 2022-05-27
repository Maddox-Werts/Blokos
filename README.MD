# BLOKOS #
### By Maddox Werts. ###

## What is this? ##
This is a simple Computer Science project I'll be working on
for the following 5 days as instructed. This project is using
the C language, so code will make more sense in this.
Also, To pronounce it, it's BLOCK * OU * SS

## Why not C++? ##
I wanted to challange myself, I'm going to use C because 
it's an older language, and one of the Most popular.

## How can I play BLOKOS? ##
There will be Two methods!
- [Downloading from the Releases Page](https://github.com/Maddox-Werts/Blokos/releases)
- [Compiling it yourself](#compiling)

## Will this recieve Updates? ##
Possibly, I may port this to 
- Nintendo Switch with LIBNX by the DevkitPro team.
- Nintendo 3DS with LIB3DS by the DevkitPro team.
- Xbox ( Original ) with the open source XDK from the community.
- Android/iOS with some SDK's here and there.

## If I'm programming for BLOKOS, What references can I have? ##
I HIGHLY recommend using this resource to help you
- [Tetris, Tetrimino Guide](https://tetris.fandom.com/wiki/Tetromino)
- [Tetris, Scoring Guide](https://tetris.wiki/Scoring)
- [Tetris, Free Online](https://bit.ly/3z0jaOl)

# Compiling #
You'll just need a few things. I'm not including ANY libraries
such as __SDL2__, __SDL2 TTF Support__. You'll need to download those from the
[DOWNLOADS](#downloads) section.

First, Use these commands to Clone, CD and Make the project
```bash
git clone https://github.com/Maddox-Werts/Blokos.git
cd Blokos
make
```

And that's it! Make sure you have the said libraries though!
Insinde my **MAKEFILE** I have it so that it automatically
launches the binaries. HOWEVER, If you're on windows, you will
manually need to insert the SDL2.dll file.

## IMPORTANT NOTICE FOR COMPILING ##
you'll need to make some modifications to the __MAKEFILE__,
As I don't have it set up to check compiling devices.
If you're compiling on MAC or APPLE devices, On the 
LIBS Variable, Make it to something like this:
```makefile
LIBS = -lsdl2main -lsdl_ttf -lsdl2
```

Otherwise, On windows, you'll need to make it
like this
```makefile
LIBS = -lsdl2main -lsdl2_ttf -lsdl2
```


# Downloads #
### TOOLS ###
[MINGW](https://sourceforge.net/projects/mingw/)
[SDL2](http://libsdl.org/download-2.0.php)
[SDL2 TTF](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.0.18)

### IDE's ( Up to you ) ###
[Visual Studio Code](https://code.visualstudio.com/)
