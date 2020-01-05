# ！bash
TARGET = main
OBJDIR = ./obj
SRCDIR = ./src
INCLUDE = ./include
CFLAGS = -std=c++11 -Wall
CC = g++
RM = -rm -f

all : $(TARGET)

main : $(SRCDIR)/main.cpp $(SRCDIR)/packagemanager.cpp $(SRCDIR)/logger.cpp $(SRCDIR)/udpserver.cpp $(SRCDIR)/simplesocket.cpp $(SRCDIR)/tcpserver.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INCLUDE) -w 

.PHONY : clean
clean : 
	$(RM) $(TARGET) $(OBJDIR)/*