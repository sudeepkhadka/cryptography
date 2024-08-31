#ifndef DEPLOY_RC4_H
#define DEPLOY_RC4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INVALID_PARAMETER -1
#define BUF_MAX 256

typedef struct
{
    unsigned int i;
    unsigned int j;
    unsigned char arr[BUF_MAX];

} Rc4Context;

void rc4Init(Rc4Context *context, const unsigned char *key, size_t length);

void rc4Cipher(Rc4Context *context, const unsigned char *input, unsigned char *output, size_t length);

#endif

/* end of file  */
