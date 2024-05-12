#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all: ugp rugp exhaust

exhaust.$(OBJ):	exhaust.c  setlib0.h 
		$(CC) -c  exhaust.c 

exhaust:	exhaust.$(OBJ) setlib0.$(OBJ)
	$(CC)  exhaust.$(OBJ) setlib0.$(OBJ)  -oexhaust
	$(MV) exhaust$(EXE) $(BIN)
#---------------------------------------------------
ugp.$(OBJ):	ugp.c  setlib0.h 
		$(CC) -c  ugp.c 

ugp:	ugp.$(OBJ) setlib0.$(OBJ)
	$(CC)  ugp.$(OBJ) setlib0.$(OBJ)  -ougp
	$(MV) ugp$(EXE) $(BIN)
#---------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#---------------------------------------------------
rugp.$(OBJ):	rugp.c 
		$(CC) -c  rugp.c 

rugp:	rugp.$(OBJ)
	$(CC)  rugp.$(OBJ)  -orugp
	$(MV) rugp$(EXE) $(BIN)
#---------------------------------------------------
