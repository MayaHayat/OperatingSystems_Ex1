#include <stdio.h>

#include <stdlib.h>

#include "libCodec.h"

// Global array of characters

char globalKey[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

char keyEncode[62] = "bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890a";

void *createCodec(char key[62])
{

    // Make sure not 2 chars are the same (mapping to different original chars)

    for (int i = 0; i < 62; i++)
    {

        for (int j = i + 1; j < 62; j++)
        {

            if (key[i] == key[j])
            {

                printf("Duplicate found, code is incorrect!");

                return NULL;
            }
        }
    }

    char *ans = (char *)malloc(125 * sizeof(char));

    if (!ans)
    {

        return NULL;
    }

    for (int i = 0; i < 62; i++)
    {

        ans[i] = globalKey[i];
    }

    for (int i = 0; i < 62; i++)
    {

        ans[62 + i] = key[i];
    }

    ans[124] = '\0';

    return ans;
}

int encode(char *textin, char *textout, int len, void *codec)
{

    if (!textin || !textout || !codec)
    {

        return -1;
    }

    int count = 0;

    char *key = (char *)codec;

    for (int i = 0; i < len; i++)
    {

        int index = -1;

        for (int j = 0; j < 62; j++)
        {

            if (textin[i] == key[j])
            {

                index = j;

                break;
            }
        }

        if (index != -1)
        {

            textout[i] = key[62 + index];

            count++;
        }

        else
        {

            textout[i] = textin[i];
        }
    }

    return count;
}

int decode(char *textin, char *textout, int len, void *codec)
{

    if (!textin || !textout || !codec)
    {

        return -1;
    }

    int count = 0;

    char *key = (char *)codec;

    for (int i = 0; i < len; i++)
    {

        int index = -1;

        for (int j = 62; j < 125; j++)
        {

            if (textin[i] == key[j])
            {

                index = j;

                break;
            }
        }

        if (index != -1)
        {

            textout[i] = key[index - 62];

            count++;
        }

        else
        {

            textout[i] = textin[i];
        }
    }

    return count;
}

void freeCodec(void *codec)
{

    free(codec);
}


int main() {

    char key[62] = "bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890a";

    // Test CREATECODEC function

    void *codec = createCodec(key);

    if (!codec) {

        return 1;

    }

    // Test ENCODE function

    char textin[] = "Hello, World!";

    char *textout = (char *)malloc((sizeof(textin) / sizeof(textin[0])) * sizeof(char));

    if (!textout) {

        printf("Memory allocation failed.\n");

        free(codec);  // Free allocated memory for the codec before exiting

        return 1;

    }

    int len = sizeof(textin) / sizeof(textin[0]);

    encode(textin, textout, len, codec);

    printf("Original Text: %s\n", textin);

    printf("Encoded Text: %s\n", textout);

    //Test DECODE function

    char textin2[] = "Ifmmp, Xpsme!";

    char *textout2 = (char *)malloc((sizeof(textin2) / sizeof(textin2[0])) * sizeof(char));

    if (!textout2) {

        printf("Memory allocation failed.\n");

        free(codec);  // Free allocated memory for the codec before exiting

        return 1;

    }

    int len2 = sizeof(textin2) / sizeof(textin2[0]);

    decode(textin2, textout2, len2, codec);

    printf("Coded Text: %s\n", textin2);

    printf("Decode Text: %s\n", textout2);

    // Free allocated memory

    free(textout);

    free(codec);

    return 0;

}

