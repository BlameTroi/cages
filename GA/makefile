#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc  -O
MV = mv
OBJ = o
EXE = 

all: ga
#--------------------------------------------------------------
ga.$(OBJ):	ga.c  setlib0.h defs.h
		$(CC) -c  ga.c 

ga:	ga.$(OBJ)  setlib0.$(OBJ)
	$(CC)  ga.$(OBJ)  setlib0.$(OBJ)  -oga
	$(MV) ga$(EXE) $(BIN)
#--------------------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#------------------------------------------------------------
