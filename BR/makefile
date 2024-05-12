
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O2 -msupersparc
MV = mv
OBJ = o
EXE =

all: sizered KR br makebasis

#--------------------------------------------#

brlib.$(OBJ):	brlib.c brlib.h
	$(CC) -c brlib.c
#--------------------------------------------#

br.$(OBJ): br.c brlib.h
	$(CC) -c br.c

br:	br.$(OBJ) brlib.$(OBJ)
	$(CC) -lm  br.$(OBJ) brlib.$(OBJ) -obr
	$(MV) br$(EXE) $(BIN)

#--------------------------------------------#
pairs.$(OBJ):	pairs.c brlib.h
	$(CC) -c pairs.c

pairs:	pairs.$(OBJ) brlib.$(OBJ)
	$(CC) -lm  pairs.$(OBJ) brlib.$(OBJ) -opairs
	$(MV) pairs$(EXE) $(BIN)

#--------------------------------------------#
triples.$(OBJ):	triples.c brlib.h
	$(CC) -c triples.c

triples:	triples.$(OBJ) brlib.$(OBJ)
	$(CC) -lm  triples.$(OBJ) brlib.$(OBJ) -otriples
	$(MV) triples$(EXE) $(BIN)

#--------------------------------------------#
KR.$(OBJ):	KR.c brlib.h
	$(CC) -c KR.c

KR:	KR.$(OBJ) brlib.$(OBJ)
	$(CC) -lm  KR.$(OBJ) brlib.$(OBJ) -oKR
	$(MV) KR$(EXE) $(BIN)

#--------------------------------------------#
sizered.$(OBJ): sizered.c brlib.h
	$(CC) -c sizered.c

sizered:	sizered.$(OBJ) brlib.$(OBJ)
	$(CC) -lm sizered.$(OBJ) brlib.$(OBJ) -osizered
	$(MV) sizered$(EXE) $(BIN)

#--------------------------------------------#

makebasis.$(OBJ):	makebasis.c 
	$(CC) -c makebasis.c

makebasis:	makebasis.$(OBJ) 
	$(CC) -lm makebasis.$(OBJ) -omakebasis
	$(MV) makebasis$(EXE) $(BIN)

