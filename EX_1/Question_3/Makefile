CC = gcc
CFLAGS = -Wall -g

all: encriptor.so encode decode

encriptor.o: libCodec.c libCodec.h
	$(CC) $(CFLAGS) -c -fPIC libCodec.c -o encriptor.o

encriptor.so: encriptor.o
	$(CC) -shared -o encriptor.so encriptor.o

mainEncode.o: mainEncode.c libCodec.h
	$(CC) $(CFLAGS) -c mainEncode.c

mainDecode.o: mainDecode.c libCodec.h
	$(CC) $(CFLAGS) -c mainDecode.c

encode: encriptor.so mainEncode.o
	$(CC) $(CFLAGS) -o encode mainEncode.o encriptor.so

decode: encriptor.so mainDecode.o
	$(CC) $(CFLAGS) -o decode mainDecode.o encriptor.so

clean:
	rm -f encriptor.o mainEncode.o mainDecode.o encode decode encriptor.so
