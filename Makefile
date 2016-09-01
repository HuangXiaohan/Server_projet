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

serverMain: serverMain.o myServer.o
	$(CC) $(CFLAGS) -o serverMain serverMain.o myServer.o

serverMain.o: serverMain.c myServer.h
	$(CC) $(CFLAGS) -c serverMain.c

myServer.o: myServer.c myServer.h
	$(CC) $(CFLAGS) -c myServer.c

myClient: myClient.c
	$(CC) $(CFLAGS) -o myClient myClient.c

clean :
	-rm *.o 