#ifndef LIBCODEC_H

#define LIBCODEC_H

extern char globalKey[62];

extern char keyEncode[62];

void *createCodec(char key[62]);

int encode(char *textin, char *textout, int len, void *codec);

int decode(char *textin, char *textout, int len, void *codec);

void freeCodec(void *codec);

#endif