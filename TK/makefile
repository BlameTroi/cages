#****** Your home directory
HOME = /home/math/kreher
#****** Where you want executable code to go
BIN = $(HOME)/bin

#CC = gcc -O2
#CC = gcc -O2 -msupersparc
#CC = gcc -O2 -g  -msupersparc
#CC = g++
CC = gcc

MV = mv
CP = cp
OBJ = o
EXE = 

first: getpairs
all:	basic goodies1 goodies2 goodies3 
basic:	gen list norb groupord reps mat
goodies1:	descert cert des2edge disp excover ext
goodies2:	getdes getorbits getorbln identity manycert
goodies3:	mat2set onksets packsets transpose transversal
goodies4:	gddreps

#----------------------------------------------------
base.$(OBJ):	base.c base.h 
		$(CC) -c base.c 
#----------------------------------------------------
setlib.$(OBJ):	setlib.c setlib.h base.h 
		$(CC) -c setlib.c 
#----------------------------------------------------
grouplib.$(OBJ):	grouplib.c grouplib.h base.h 
			$(CC) -c grouplib.c 
#----------------------------------------------------
orblib.$(OBJ):	orblib.c orblib.h base.h 
		$(CC) -c orblib.c 
#----------------------------------------------------
isolib.$(OBJ):	isolib.c isolib.h base.h 
		$(CC) -c isolib.c 
#----------------------------------------------------
graphlib.$(OBJ):	graphlib.c graphlib.h base.h 
		$(CC) -c graphlib.c 
#----------------------------------------------------
excover.$(OBJ):	excover.c setlib.h
		$(CC) -c excover.c

excover:	base.$(OBJ) setlib.$(OBJ) excover.$(OBJ) 
		$(CC) base.$(OBJ) setlib.$(OBJ) excover.$(OBJ) -oexcover
		$(MV) excover$(EXE) $(BIN)
#----------------------------------------------------
gen.$(OBJ):	gen.c setlib.h grouplib.h
		$(CC) -c gen.c

gen:		base.$(OBJ) gen.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) gen.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -ogen
		$(MV) gen$(EXE) $(BIN)
#----------------------------------------------------
transpose.$(OBJ):	transpose.c
		$(CC) -c transpose.c 

transpose:		base.$(OBJ) transpose.$(OBJ)
		$(CC) transpose.$(OBJ) -otranspose
		$(MV) transpose$(EXE) $(BIN)
#----------------------------------------------------
disp.$(OBJ):	disp.c setlib.h grouplib.h
		$(CC) -c disp.c 

disp:		base.$(OBJ) disp.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) disp.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -odisp
		$(MV) disp$(EXE) $(BIN)
#----------------------------------------------------
getdes.$(OBJ):	getdes.c setlib.h 
		$(CC) -c getdes.c 

getdes:		base.$(OBJ) getdes.$(OBJ) setlib.$(OBJ) 
		$(CC) base.$(OBJ) getdes.$(OBJ) setlib.$(OBJ)  -ogetdes
		$(MV) getdes$(EXE) $(BIN)
#----------------------------------------------------
dispinc.$(OBJ):	dispinc.c setlib.h grouplib.h
		$(CC) -c dispinc.c 

dispinc:		base.$(OBJ) dispinc.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) dispinc.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -odispinc
		$(MV) dispinc$(EXE) $(BIN)
#----------------------------------------------------
packsets.$(OBJ):	packsets.c setlib.h
		$(CC) -c packsets.c 

packsets:		base.$(OBJ) packsets.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) packsets.$(OBJ) setlib.$(OBJ) -opacksets
		$(MV) packsets$(EXE) $(BIN)
#----------------------------------------------------
set2pairs.$(OBJ):	set2pairs.c setlib.h grouplib.h
		$(CC) -c set2pairs.c 

set2pairs:		base.$(OBJ) set2pairs.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) set2pairs.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -oset2pairs
		$(MV) set2pairs$(EXE) $(BIN)
#----------------------------------------------------
list.$(OBJ):	list.c setlib.h grouplib.h
		$(CC) -c list.c 

list:		base.$(OBJ) list.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) list.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -olist
		$(MV) list$(EXE) $(BIN)
#----------------------------------------------------
norb.$(OBJ):	norb.c setlib.h grouplib.h
		$(CC) -c norb.c 

norb:		base.$(OBJ) norb.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) norb.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -onorb
		$(MV) norb$(EXE) $(BIN)
#----------------------------------------------------
groupord.$(OBJ):	groupord.c setlib.h grouplib.h
		$(CC) -c groupord.c 

groupord:	base.$(OBJ) groupord.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) groupord.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -ogroupord
		$(MV) groupord$(EXE) $(BIN)
#----------------------------------------------------
onksets.$(OBJ):	onksets.c grouplib.h setlib.h
		$(CC) -c onksets.c 

onksets:	base.$(OBJ) onksets.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) onksets.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) -oonksets
		$(MV) onksets$(EXE) $(BIN)
#----------------------------------------------------
onordpairs.$(OBJ):	onordpairs.c grouplib.h setlib.h
		$(CC) -c onordpairs.c 

onordpairs:	base.$(OBJ) onordpairs.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) onordpairs.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) -oonordpairs
		$(MV) onordpairs$(EXE) $(BIN)
#----------------------------------------------------
ext.$(OBJ):	ext.c setlib.h
		$(CC) -c ext.c 

ext:		base.$(OBJ) ext.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) ext.$(OBJ) setlib.$(OBJ) -oext
		$(MV) ext$(EXE) $(BIN)
#----------------------------------------------------
des2edge.$(OBJ):	des2edge.c setlib.h
		$(CC) -c des2edge.c 

des2edge:	des2edge.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) des2edge.$(OBJ) setlib.$(OBJ) -odes2edge
		$(MV) des2edge$(EXE) $(BIN)
#----------------------------------------------------
mat2set.$(OBJ):	mat2set.c setlib.h
		$(CC) -c mat2set.c 

mat2set:	mat2set.$(OBJ) setlib.$(OBJ) base.$(OBJ)
		$(CC) base.$(OBJ) mat2set.$(OBJ) setlib.$(OBJ) -omat2set
		$(MV) mat2set$(EXE) $(BIN)
#----------------------------------------------------
identity.$(OBJ):	identity.c setlib.h grouplib.h
		$(CC) -c identity.c 

identity:	base.$(OBJ) identity.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) identity.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) -oidentity
		$(MV) identity$(EXE) $(BIN)
#----------------------------------------------------
reps.$(OBJ):	reps.c grouplib.h setlib.h orblib.h
		$(CC) -c reps.c

reps:		reps.$(OBJ) base.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ)
		$(CC) base.$(OBJ) reps.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ) -oreps
		$(MV) reps$(EXE) $(BIN)

#----------------------------------------------------
modreps.$(OBJ):	modreps.c graphlib.h grouplib.h setlib.h orblib.h
		$(CC) -c modreps.c

modreps:	modreps.$(OBJ) base.$(OBJ) graphlib.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ)
		$(CC) base.$(OBJ) modreps.$(OBJ) graphlib.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ) -omodreps
		$(MV) modreps$(EXE) $(BIN)

#----------------------------------------------------
descert.o:	descert.c grouplib.h setlib.h isolib.h graphlib.h
	$(CC) -c descert.c
descert:	descert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ)
	$(CC) descert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) -o descert
	$(MV) descert$(EXE) $(BIN)
#----------------------------------------------------
cert.$(OBJ):	cert.c grouplib.h setlib.h isolib.h graphlib.h
		$(CC) -c cert.c

cert:	cert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) 
	$(CC) cert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) -o cert
		$(MV) cert$(EXE) $(BIN)
#---------------------------------------------------

morecert.$(OBJ):	morecert.c grouplib.h setlib.h isolib.h graphlib.h
		$(CC) -c morecert.c

morecert:	morecert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) 
	$(CC) morecert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) -o morecert
		$(MV) morecert$(EXE) $(BIN)

#---------------------------------------------------
mat.$(OBJ):	mat.c orblib.h setlib.h grouplib.h 
		$(CC) -c mat.c

mat:	mat.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ)
	$(CC) mat.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ) -omat
	$(MV) mat$(EXE) $(BIN)
#---------------------------------------------------
getorbits.$(OBJ):	getorbits.c orblib.h setlib.h grouplib.h 
		$(CC) -c getorbits.c

getorbits:	getorbits.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ)
	$(CC) getorbits.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ) -ogetorbits
	$(MV) getorbits$(EXE) $(BIN)
#----------------------------------------------------
getorb2.$(OBJ):	getorb2.c orblib.h setlib.h grouplib.h 
		$(CC) -c getorb2.c

getorb2:	getorb2.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ)
	$(CC) getorb2.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ) -ogetorb2
	$(MV) getorb2$(EXE) $(BIN)
#----------------------------------------------------
getorbln.$(OBJ):	getorbln.c orblib.h setlib.h grouplib.h 
		$(CC) -c getorbln.c

getorbln:	getorbln.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ)
	$(CC) getorbln.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ) -ogetorbln
	$(MV) getorbln$(EXE) $(BIN)
#----------------------------------------------------
manycert.$(OBJ):	manycert.c grouplib.h setlib.h isolib.h graphlib.h
		$(CC) -c manycert.c

manycert:	manycert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) 
	$(CC) manycert.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) graphlib.$(OBJ) isolib.$(OBJ) -o manycert
		$(MV) manycert$(EXE) $(BIN)

#----------------------------------------------------
transversal.$(OBJ):	transversal.c setlib.h grouplib.h
	$(CC) -c transversal.c

transversal:	base.$(OBJ) transversal.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) transversal.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -otransversal
		$(MV) transversal$(EXE) $(BIN)
#----------------------------------------------------
certext.$(OBJ):	certext.c base.h setlib.h
		$(CC) -c certext.c 

certext:	certext.$(OBJ) base.$(OBJ) setlib.$(OBJ)
		$(CC) certext.$(OBJ) base.$(OBJ) setlib.$(OBJ) -ocertext
		$(MV) certext$(EXE) $(BIN)
#----------------------------------------------------
A4check.$(OBJ):	A4check.c setlib.h grouplib.h
	$(CC) -c A4check.c

A4check:	base.$(OBJ) A4check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) A4check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -oA4check
		$(MV) A4check$(EXE) $(BIN)
#----------------------------------------------------
S3check.$(OBJ):	S3check.c setlib.h grouplib.h
	$(CC) -c S3check.c

S3check:	base.$(OBJ) S3check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) S3check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -oS3check
		$(MV) S3check$(EXE) $(BIN)
#----------------------------------------------------
C3check.$(OBJ):	C3check.c setlib.h grouplib.h
	$(CC) -c C3check.c

C3check:	base.$(OBJ) C3check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) C3check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -oC3check
		$(MV) C3check$(EXE) $(BIN)
#----------------------------------------------------
S4check.$(OBJ):	S4check.c setlib.h grouplib.h
	$(CC) -c S4check.c

S4check:	base.$(OBJ) S4check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) S4check.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -oS4check
		$(MV) S4check$(EXE) $(BIN)
#----------------------------------------------------
onefact.$(OBJ):	onefact.c
		$(CC) -c onefact.c

onefact:	onefact.$(OBJ)
		$(CC) onefact.$(OBJ) -oonefact
#----------------------------------------------------
on1f.$(OBJ):	on1f.c grouplib.h setlib.h
		$(CC) -c on1f.c

on1f:	base.$(OBJ) on1f.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ)
	$(CC) on1f.$(OBJ) base.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) -oon1f
	$(MV) on1f$(EXE) $(BIN)
#----------------------------------------------------

sticks.$(OBJ):	sticks.c
		$(CC) -c sticks.c

sticks:	sticks.$(OBJ)
	$(CC) sticks.$(OBJ) -osticks
	$(MV) sticks$(EXE) $(BIN)
#----------------------------------------------------
gddreps.$(OBJ):	gddreps.c grouplib.h setlib.h orblib.h
		$(CC) -c gddreps.c

gddreps:		gddreps.$(OBJ) base.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ)
		$(CC) base.$(OBJ) gddreps.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ) -ogddreps
		$(MV) gddreps$(EXE) $(BIN)

#----------------------------------------------------

prim.$(OBJ):	prim.c
		$(CC) -DP=\"$(BIN)\" -c prim.c

prim:	prim.$(OBJ)
	$(CP) PGD $(BIN)
	$(CC) prim.$(OBJ) -oprim
	$(MV) prim$(EXE) $(BIN)
#----------------------------------------------------
SSCK.$(OBJ):	SSCK.c setlib.h 
		$(CC) -c SSCK.c 

SSCK:		base.$(OBJ) SSCK.$(OBJ) setlib.$(OBJ) 
		$(CC) base.$(OBJ) SSCK.$(OBJ) setlib.$(OBJ)  -oSSCK
		$(MV) SSCK$(EXE) $(BIN)
#----------------------------------------------------
matD.$(OBJ):	matD.c orblib.h setlib.h grouplib.h 
		$(CC) -c matD.c

matD:	matD.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ)
	$(CC) matD.$(OBJ) base.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) orblib.$(OBJ) -omatD
	$(MV) matD$(EXE) $(BIN)
#---------------------------------------------------
dispair.$(OBJ):	dispair.c setlib.h
		$(CC) -c dispair.c 

dispair:	base.$(OBJ) dispair.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) dispair.$(OBJ) setlib.$(OBJ) -odispair
		$(MV) dispair$(EXE) $(BIN)
#----------------------------------------------------
reps1.$(OBJ):	reps1.c grouplib.h setlib.h orblib.h
		$(CC) -c reps1.c

reps1:		reps1.$(OBJ) base.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ)
		$(CC) base.$(OBJ) reps1.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ) -oreps1
		$(MV) reps1$(EXE) $(BIN)

#----------------------------------------------------
findreps.$(OBJ):	findreps.c grouplib.h setlib.h orblib.h
		$(CC) -c findreps.c

findreps:		findreps.$(OBJ) base.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ)
		$(CC) base.$(OBJ) findreps.$(OBJ) grouplib.$(OBJ) setlib.$(OBJ) orblib.$(OBJ) -ofindreps
		$(MV) findreps$(EXE) $(BIN)

#----------------------------------------------------
findassoc.$(OBJ):	findassoc.c setlib.h
		$(CC) -c findassoc.c 

findassoc:		base.$(OBJ) findassoc.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) findassoc.$(OBJ) setlib.$(OBJ) -ofindassoc
		$(MV) findassoc$(EXE) $(BIN)
#----------------------------------------------------
Tfindassoc.$(OBJ):	Tfindassoc.c setlib.h
		$(CC) -c Tfindassoc.c 

Tfindassoc:		base.$(OBJ) Tfindassoc.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) Tfindassoc.$(OBJ) setlib.$(OBJ) -oTfindassoc
		$(MV) Tfindassoc$(EXE) $(BIN)
#----------------------------------------------------
x.$(OBJ):	x.c setlib.h
		$(CC) -c x.c 

x:		base.$(OBJ) x.$(OBJ) setlib.$(OBJ)
		$(CC) base.$(OBJ) x.$(OBJ) setlib.$(OBJ) -ox
		$(MV) x$(EXE) $(BIN)
#----------------------------------------------------
disp2.$(OBJ):	disp2.c setlib.h grouplib.h
		$(CC) -c disp2.c 

disp2:		base.$(OBJ) disp2.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) disp2.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -odisp2
		$(MV) disp2$(EXE) $(BIN)
#----------------------------------------------------
nautydisp.$(OBJ):	nautydisp.c setlib.h grouplib.h
	$(CC) -c nautydisp.c

nautydisp:	base.$(OBJ) nautydisp.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
	$(CC) base.$(OBJ) nautydisp.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -onautydisp
	$(MV) nautydisp$(EXE) $(BIN)

#----------------------------------------------------
getpairs.$(OBJ):	getpairs.c setlib.h grouplib.h
		$(CC) -c getpairs.c 

getpairs:		base.$(OBJ) getpairs.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) getpairs.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -ogetpairs
		$(MV) getpairs$(EXE) $(BIN)
#----------------------------------------------------
rightreg.$(OBJ):	rightreg.c setlib.h grouplib.h
		$(CC) -c rightreg.c

rightreg:		base.$(OBJ) rightreg.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ)
		$(CC) base.$(OBJ) rightreg.$(OBJ) setlib.$(OBJ) grouplib.$(OBJ) -orightreg
		$(MV) rightreg$(EXE) $(BIN)
#----------------------------------------------------
sets2edges.$(OBJ):	sets2edges.c setlib.h 
			$(CC) -c sets2edges.c

sets2edges:	base.$(OBJ) sets2edges.$(OBJ) setlib.$(OBJ) 
		$(CC) base.$(OBJ) sets2edges.$(OBJ) setlib.$(OBJ) -osets2edges
		$(MV) sets2edges$(EXE) $(BIN)

#----------------------------------------------------
classify.$(OBJ):	classify.c setlib.h 
			$(CC) -c classify.c

classify:	base.$(OBJ) classify.$(OBJ) setlib.$(OBJ) 
		$(CC) base.$(OBJ) classify.$(OBJ) setlib.$(OBJ) -oclassify
		$(MV) classify$(EXE) $(BIN)

#----------------------------------------------------
