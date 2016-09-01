# Compilateur
#INC=-I/usr/local/include  
#LIB=-L/usr/local/lib   

CC = gcc 

# Options de compilation : -g pour débugger, compatibilité ANSI et niveau de
# warning maximum 
CFLAGS =-g -std=gnu99 -Wall

#------------------------------------------------------------------
# Cibles principales
#------------------------------------------------------------------

all: serverMain myClient

serverMain: serverMain.o
	$(CC) $(CFLAGS) -o serverMain serverMain.o

serverMain.o: serverMain.c myServer.h
	$(CC) $(CFLAGS) -c serverMain.c

myClient: myClient.c
	$(CC) $(CFLAGS) -o myClient myClient.c

clean :
	-rm *.o 