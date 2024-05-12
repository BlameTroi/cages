CC = gcc
MV = mv
OBJ = o
EXE = 

all: tree2cert cert2tree

#----------------------------------------------------
setlib0.$(OBJ):	setlib0.c setlib0.h defs.h
		$(CC) -c setlib0.c
#----------------------------------------------------
tree2cert.$(OBJ):	tree2cert.c 
		$(CC) -c tree2cert.c

tree2cert:	tree2cert.$(OBJ) setlib0.$(OBJ) 
	$(CC) tree2cert.$(OBJ) setlib0.$(OBJ) -otree2cert
#----------------------------------------------------
cert2tree.$(OBJ):	cert2tree.c 
		$(CC) -c cert2tree.c

cert2tree:	cert2tree.$(OBJ) setlib0.$(OBJ) 
	$(CC) cert2tree.$(OBJ) setlib0.$(OBJ) -ocert2tree
#----------------------------------------------------
