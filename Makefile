# ！bash
TARGET = ts
OBJDIR = ./obj
SRCDIR = ./src
INCLUDE = ./include
CFLAGS = -std=c++11 -Wall
CC = g++
RM = -rm -f

all : $(TARGET)

ts : $(SRCDIR)/main.cpp $(SRCDIR)/Tcpsocket.cpp $(SRCDIR)/Logger.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INCLUDE) -w 

.PHONY : clean
clean : 
	$(RM) $(TARGET) $(OBJDIR)/*