#***************************************************************************
 # Object Oriented Programming Using C++ CPT323
 # Assignment 2 - RMIT SP1 2020
 # @author Miroslav Petkovic s3666906 & Jarryd Semmens
 # Makefile
 # Assists in loading game in line command
 #
 #***************************************************************************
CXXFLAGS=-ansi -Wall -pedantic -Wextra -g -std=c++2a 
LDFLAGS=
OBJECTS=Area.o AreaManager.o Door.o DoorManager.o EnumParser.o ILoadObject.o ISaveObject.o Item.o ItemManager.o ManagerBase.o MathHelper.o Player.o PlayerManager.o PorkGame.o Room.o RoomManager.o RoomState.o RoomStateManager.o StringHelper.o main.o
HEADERS=Area.h AreaManager.h Door.h DoorManager.h EnumParser.h ILoadObject.h ISaveObject.h Item.h ItemManager.h ManagerBase.h MathHelper.h Player.h PlayerManager.h PorkGame.h Room.h RoomManager.h RoomState.h RoomStateManager.h StringHelper.h
CC=g++

all:pork

pork: ${OBJECTS}
	${CXX} ${LDFLAGS} ${OBJECTS} -o $@ -lboost_filesystem -lboost_system

%.o:%.cpp ${HEADERS}
	${CC} ${CCFLAGS} -c $<

clean:
	rm -f *.o pork

##########