# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = Libfdr/
INCLUDE = -I$(CLASSDIR)/include
LIBS = $(CLASSDIR)/lib/libfdr.a
CC = gcc

EX  =  bin/main 
       
all: $(EX) 

clean: 
	rm -f bin/*

bin/main: src/main.c $(LIBS)
	$(CC) $(INCLUDE) -o bin/main src/main.c $(LIBS)

