
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE =


all: allcliq maxc rg

#------------------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#------------------------------------------------------------
allcliq.$(OBJ):	allcliq.c setlib0.h 
		$(CC) -c allcliq.c

allcliq:	allcliq.$(OBJ) setlib0.$(OBJ)
		$(CC) allcliq.$(OBJ) setlib0.$(OBJ)  -oallcliq
		$(MV) allcliq $(BIN)
#------------------------------------------------------------
maxc.$(OBJ):	maxc.c setlib0.h 
		$(CC) -c maxc.c

maxc:		maxc.$(OBJ) setlib0.$(OBJ) 
		$(CC) maxc.$(OBJ) setlib0.$(OBJ) -omaxc
		$(MV) maxc $(BIN)
#------------------------------------------------------------
rg.$(OBJ):	rg.c
	$(CC) -c rg.c

rg:	rg.$(OBJ) 
	$(CC) rg.$(OBJ) -org
	$(MV) rg $(BIN)
#------------------------------------------------------------
