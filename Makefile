CC=g++
CFLAGS=-Wall `sdl-config --cflags` -I../engine `pkg-config --cflags ftgl` -g
LIBS=`sdl-config --libs` -L../engine -ldemoframework `pkg-config --libs ftgl` -lGL -lGLU -lGLee -lSDL_net -lSDL_mixer
OBJ=CPlasmaWeapon.o globals.o CNetworkManager.o Demo.o CShip.o CMessageQueue.o CCubicSpline.o main.o 

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o slaughter $(LIBS)
	
.cpp.o: 
	$(CC) $(CFLAGS) -c $<
.PHONY: clean

clean:
	rm -f *.o slaughter