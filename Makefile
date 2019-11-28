all: graph

CFLAGS=-g -Og -Wall -std=c99
CC=gcc

graph: main.c graph.c
				$(CC) $(CFLAGS) -o $@ $^

clean:
				rm -f graph
