
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all:	sa

#-------------------------------------------------
sa.$(OBJ):	sa.c 
	$(CC) -c sa.c

sa:	sa.$(OBJ) 
	$(CC) sa.$(OBJ) -lm -osa
	$(MV) sa$(EXE) $(BIN)
#-------------------------------------------------
