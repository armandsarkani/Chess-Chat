# Makefile for Chesster, EECS22L Winter 2019
# Author: Marvis Nguyen
# Modified by: Marvis Nguyen

GTKINC	= `pkg-config --cflags gtk+-2.0 gthread-2.0`
GTKLIBS	= `pkg-config --libs gtk+-2.0 gthread-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS = -g
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99
# LFLAGS: -Wall
#ASCII: bin/Chess clean

all:  bin/Client bin/Server bin/GUIClient bin/RemoteGUIClient bin/RemoteClient clean
Client: bin/Client clean
RemoteClient: bin/RemoteClient clean
GUIClient: bin/GUIClient clean
RemoteGUIClient: bin/RemoteGUIClient clean
Server: bin/Server clean

bin/Client: bin/Client.o bin/Board.o bin/Pieces.o bin/Movegen.o bin/Conditions.o bin/FriendsList.o 
	$(CC)  bin/Board.o bin/Client.o bin/Pieces.o bin/Movegen.o bin/Conditions.o bin/FriendsList.o $(OPTS) -pthread -o bin/Client

bin/RemoteClient: bin/RemoteClient.o bin/Board.o bin/Pieces.o bin/Movegen.o bin/Conditions.o bin/RemoteFriendsList.o 
	$(CC)  bin/Board.o bin/RemoteClient.o bin/Pieces.o bin/Movegen.o bin/Conditions.o bin/RemoteFriendsList.o $(OPTS) -pthread -o bin/RemoteClient

bin/Server: bin/Server.o bin/Board.o bin/Pieces.o bin/Movegen.o bin/Conditions.o 
	$(CC) bin/Board.o bin/Server.o bin/Pieces.o bin/Movegen.o bin/Conditions.o $(OPTS) -pthread -o bin/Server

bin/GUIClient: bin/Board.o bin/Movegen.o bin/Conditions.o bin/Pieces.o bin/chatGUI.o bin/list.o bin/ChatWindow.o bin/ClientFunctions.o bin/FriendsList.o
	$(CC) $(LFLAGS) bin/Board.o bin/Movegen.o bin/Conditions.o bin/Pieces.o bin/chatGUI.o bin/list.o bin/ChatWindow.o bin/ClientFunctions.o bin/FriendsList.o $(LIBS) $(OPTS) -o bin/GUIClient

bin/RemoteGUIClient: bin/Board.o bin/Movegen.o bin/Conditions.o bin/Pieces.o bin/chatGUI.o bin/remotelist.o bin/ChatWindow.o bin/ClientFunctions.o bin/RemoteFriendsList.o
	$(CC) $(LFLAGS) bin/Board.o bin/Movegen.o bin/Conditions.o bin/Pieces.o bin/chatGUI.o bin/remotelist.o bin/ChatWindow.o bin/ClientFunctions.o bin/RemoteFriendsList.o $(LIBS) $(OPTS) -o bin/RemoteGUIClient

bin/FriendsList.o: src/FriendsList.c src/FriendsList.h
	$(CC) $(OPTS) $(CFLAGS) src/FriendsList.c -o bin/FriendsList.o

bin/RemoteFriendsList.o: src/RemoteFriendsList.c src/RemoteFriendsList.h
	$(CC) $(OPTS) $(CFLAGS) src/RemoteFriendsList.c -o bin/RemoteFriendsList.o
	
bin/Board.o: src/Board.c src/Board.h src/Pieces.h src/Movegen.h src/Conditions.h
	$(CC) $(CFLAGS) src/Board.c -o bin/Board.o

bin/Client.o: src/Client.c src/Board.h
	$(CC) $(OPTS) $(CFLAGS) src/Client.c -pthread -o bin/Client.o

bin/RemoteClient.o: src/RemoteClient.c src/Board.h
	$(CC) $(OPTS) $(CFLAGS) src/RemoteClient.c -pthread -o bin/RemoteClient.o

bin/Server.o: src/Server.c src/Board.h
	$(CC) $(OPTS) $(CFLAGS) src/Server.c -pthread -o bin/Server.o

bin/Pieces.o: src/Pieces.c src/Pieces.h src/Board.h src/Conditions.h
	$(CC) $(CFLAGS) src/Pieces.c -o bin/Pieces.o

bin/Movegen.o: src/Movegen.c src/Movegen.h src/Pieces.h src/Board.h src/Conditions.h
	$(CC) $(CFLAGS) src/Movegen.c -o bin/Movegen.o

bin/Conditions.o: src/Conditions.c src/Conditions.h src/Board.h src/Pieces.h
	$(CC) $(CFLAGS) src/Conditions.c -o bin/Conditions.o

#bin/GTK_chess.o: src/GTK_chess.c src/GTK_chess.h src/Board.h
#	$(CC) $(CFLAGS) src/GTK_chess.c $(INC) $(OPTS) -o bin/GTK_chess.o

bin/ClientFunctions.o: src/ClientFunctions.c src/ClientFunctions.h 
	$(CC) $(OPTS) $(CFLAGS) src/ClientFunctions.c -pthread -o bin/ClientFunctions.o

bin/ChatWindow.o: src/ChatWindow.c src/Board.h src/GTK_chess.h src/ChatWindow.h
	$(CC) $(CFLAGS) src/ChatWindow.c $(INC) $(OPTS) -o bin/ChatWindow.o

bin/list.o: src/list.c src/list.h src/FriendsList.h
	$(CC) $(CFLAGS) src/list.c $(INC) $(OPTS) -o bin/list.o

bin/remotelist.o: src/remotelist.c src/list.h src/RemoteFriendsList.h
	$(CC) $(CFLAGS) src/remotelist.c $(INC) $(OPTS) -o bin/remotelist.o

bin/chatGUI.o: src/chatGUI.c src/chatGUI.h
	$(CC) $(CFLAGS) src/chatGUI.c $(INC) $(OPTS) -o bin/chatGUI.o


clean:
	rm -f bin/*.o $(GUI)

tar:
	tar -czvf Chess_V1.0_src.tar.gz src
	

