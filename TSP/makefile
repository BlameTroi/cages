#****** Your home directory
HOME = .
#****** Where you want the executable code to go
BIN = $(HOME)/build/

CC = clang -O
MV = mv
OBJ = o
EXE = 

all: rtsp tsp

#----------------------------------------------------
tsp.$(OBJ):	tsp.c setlib0.h 
		$(CC) -c tsp.c 

tsp:	tsp.$(OBJ) setlib0.$(OBJ)
	$(CC) tsp.$(OBJ) setlib0.$(OBJ) -otsp
	$(MV) tsp$(EXE) $(BIN)
#----------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#--------------------------------------------------
rtsp.$(OBJ):	rtsp.c 
		$(CC) -c rtsp.c 

rtsp:	rtsp.$(OBJ)
	$(CC) rtsp.$(OBJ) -ortsp
	$(MV) rtsp$(EXE) $(BIN)
#----------------------------------------------------
