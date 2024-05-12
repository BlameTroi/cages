
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all:  tabu randks

#-------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC)    -c  setlib0.c
#-------------------------------------------------
tabu.$(OBJ):    tabu.c setlib0.h
		$(CC) -c  tabu.c
 
tabu:	setlib0.$(OBJ) tabu.$(OBJ) 
	$(CC) tabu.$(OBJ) setlib0.$(OBJ) -otabu
	$(MV) tabu$(EXE) $(BIN)
#-------------------------------------------------
randks.$(OBJ):	randks.c
	$(CC)   -c  randks.c
randks:	randks.o
	$(CC)  randks.$(OBJ) -orandks
	$(MV)  randks$(EXE) $(BIN)
#-------------------------------------------------

