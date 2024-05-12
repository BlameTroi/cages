
#****** Your home directory
HOME = /home/math/kreher
#****** Where you want the executable code to go
BIN  = $(HOME)/bin

CC = gcc -O
MV = mv
OBJ = o
EXE = 


all:	C1a C1b C2

C1a:	ksubsetcolex revdoor TrotterJohnson

C1b:	ksubsetlex subsetlex graycode permlex

C2:	IntegerPartitions

C3:	catalan prufer rgf 

#-------------------------------------------------
IntegerPartitions.$(OBJ):	IntegerPartitions.c 
	$(CC) -c IntegerPartitions.c

IntegerPartitions:	IntegerPartitions.$(OBJ) 
	$(CC) IntegerPartitions.$(OBJ) -oIntegerPartitions
	$(MV) IntegerPartitions$(EXE) $(BIN)

#-------------------------------------------------
TrotterJohnson.$(OBJ):	TrotterJohnson.c 
	$(CC) -c TrotterJohnson.c

TrotterJohnson:	TrotterJohnson.$(OBJ) 
	$(CC) TrotterJohnson.$(OBJ) -oTrotterJohnson
	$(MV) TrotterJohnson$(EXE) $(BIN)

#-------------------------------------------------
graycode.$(OBJ):	graycode.c 
	$(CC) -c graycode.c

graycode:	graycode.$(OBJ) 
	$(CC) graycode.$(OBJ) -ograycode
	$(MV) graycode$(EXE) $(BIN)

#-------------------------------------------------
ksubsetcolex.$(OBJ):	ksubsetcolex.c 
	$(CC) -c ksubsetcolex.c

ksubsetcolex:	ksubsetcolex.$(OBJ) 
	$(CC) ksubsetcolex.$(OBJ) -oksubsetcolex
	$(MV) ksubsetcolex$(EXE) $(BIN)

#-------------------------------------------------
ksubsetlex.$(OBJ):	ksubsetlex.c 
	$(CC) -c ksubsetlex.c

ksubsetlex:	ksubsetlex.$(OBJ) 
	$(CC) ksubsetlex.$(OBJ) -oksubsetlex
	$(MV) ksubsetlex$(EXE) $(BIN)

#-------------------------------------------------
permlex.$(OBJ):	permlex.c 
	$(CC) -c permlex.c

permlex:	permlex.$(OBJ) 
	$(CC) permlex.$(OBJ) -opermlex
	$(MV) permlex$(EXE) $(BIN)

#-------------------------------------------------
revdoor.$(OBJ):	revdoor.c 
	$(CC) -c revdoor.c

revdoor:	revdoor.$(OBJ) 
	$(CC) revdoor.$(OBJ) -orevdoor
	$(MV) revdoor$(EXE) $(BIN)

#-------------------------------------------------
subsetlex.$(OBJ):	subsetlex.c 
	$(CC) -c subsetlex.c

subsetlex:	subsetlex.$(OBJ) 
	$(CC) subsetlex.$(OBJ) -osubsetlex
	$(MV) subsetlex$(EXE) $(BIN)
#-------------------------------------------------
catalan.$(OBJ):	catalan.c 
	$(CC) -c catalan.c

catalan:	catalan.$(OBJ) 
	$(CC) catalan.$(OBJ) -ocatalan
	$(MV) catalan$(EXE) $(BIN)
#-------------------------------------------------
prufer.$(OBJ):	prufer.c 
	$(CC) -c prufer.c

prufer:	prufer.$(OBJ) 
	$(CC) prufer.$(OBJ) -oprufer
	$(MV) prufer$(EXE) $(BIN)
#-------------------------------------------------
rgf.$(OBJ):	rgf.c setlib0.h
	$(CC) -c rgf.c

rgf:	rgf.$(OBJ)   setlib0.$(OBJ)
	$(CC) rgf.$(OBJ)  setlib0.$(OBJ) -orgf
	$(MV) rgf$(EXE) $(BIN)
#-------------------------------------------------
