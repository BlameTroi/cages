
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all: excover

#--------------------------------------------------------------
setlib.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#--------------------------------------------------------------
excover.$(OBJ):	excover.c setlib0.h
		$(CC) -c excover.c

excover:	excover.$(OBJ) setlib0.$(OBJ)
		$(CC) excover.$(OBJ) setlib0.$(OBJ) -oexcover
		$(MV) excover$(EXE) $(BIN)
#--------------------------------------------------------------
