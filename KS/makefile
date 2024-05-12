
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 

all:	knaps1 knaps2 knaps3 knaps123 randks

#----------------------------------------------------
knaps1.$(OBJ):    knaps1.c
		$(CC) -c  knaps1.c
 
knaps1:	knaps1.$(OBJ)
		$(CC) knaps1.$(OBJ) -oknaps1
		$(MV) knaps1$(EXE) $(BIN)
#-------------------------------------------------
knaps2.$(OBJ):	knaps2.c
		$(CC) -c  knaps2.c
 
knaps2:	knaps2.$(OBJ)
		$(CC) knaps2.$(OBJ) -oknaps2
		$(MV) knaps2$(EXE) $(BIN)
#-------------------------------------------------
knaps3.$(OBJ):	knaps3.c
		$(CC) -c  knaps3.c
 
knaps3:	knaps3.$(OBJ)
		$(CC) knaps3.$(OBJ) -oknaps3
		$(MV) knaps3$(EXE) $(BIN)
#----------------------------------------------------
knaps123.$(OBJ):    knaps123.c
		$(CC) -c  knaps123.c
 
knaps123:	knaps123.$(OBJ)
		$(CC) knaps123.$(OBJ) -oknaps123
		$(MV) knaps123$(EXE) $(BIN)
#-------------------------------------------------
randks.$(OBJ):	randks.c
	$(CC)   -c  randks.c

randks:	randks.o 
	$(CC)  randks.$(OBJ) -orandks
	$(MV)  randks$(EXE) $(BIN)
#----------------------------------------------------
