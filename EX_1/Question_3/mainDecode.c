#include <stdio.h>
#include <stdlib.h>
#include "libCodec.h"

int main(int argc, char *argv[])
{
    (void)argc;
    FILE *src_file = fopen(argv[1], "r");
    FILE *dst_file = fopen(argv[2], "w");

    if (!src_file || !dst_file)
    {
        printf("Couldn't open files.");
        return 1;
    }

    fseek(src_file, 0, SEEK_END);
    long fileSize = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);

    void *codec = createCodec(keyEncode); // Use keyDecode for decoding
    if (!codec)
    {
        printf("Couldn't access codec!");
        return 1;
    }

    char *fileContent = (char *)malloc(fileSize + 1); // +1 for the null terminator
    if (!fileContent)
    {
        perror("Error allocating memory");
        fclose(src_file);
        return 1;
    }

    // Read the file content into the allocated memory
    if (fread(fileContent, 1, fileSize, src_file) != fileSize)
    {
        perror("Error reading file");
        free(fileContent);
        fclose(src_file);
        return 1;
    }

    // Null-terminate the content to make it a valid C string

    fileContent[fileSize] = '\0';
    char *textout = (char *)malloc(fileSize + 1);
    decode(fileContent, textout, fileSize, codec); // Use decode function

    // Write the line to the file

    if (fputs(textout, dst_file) == EOF)
    {
        perror("Error writing to file");
        fclose(dst_file);
        return 1;
    }

    // Free allocated memory and close files

    freeCodec(codec);
    fclose(src_file);
    fclose(dst_file);

    return 0;
}