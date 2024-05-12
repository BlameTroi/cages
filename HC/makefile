
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all:	stinsonalg

#-------------------------------------------------
stinsonalg.$(OBJ):	stinsonalg.c 
	$(CC) -c stinsonalg.c

stinsonalg:	stinsonalg.$(OBJ) 
	$(CC) stinsonalg.$(OBJ) -ostinsonalg
	$(MV) stinsonalg$(EXE) $(BIN)
#-------------------------------------------------
