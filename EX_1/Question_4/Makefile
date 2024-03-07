CC = gcc
CFLAGS = -Wall -g

.PHONY: all clean

all: myzip myunzip

myunzip: myunzip.c
	$(CC) $(CFLAGS) $^ -o $@

myzip: myzip.c
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -f myzip myunzip