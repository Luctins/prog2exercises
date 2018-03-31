#----------------------
#----------------------
#---@file Makefile
#---@author Lucas Martins Mendes
#---
#----------------------
#----------------------


CFLAGS=-lm
CC=gcc
PROJ_NAME=stockc
DEPS=exerc_pto.h
OBJ := $(wildcard *.o)

$(PROJ_NAME) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
