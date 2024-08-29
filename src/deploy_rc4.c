// Reference - https://www.oryx-embedded.com/doc/rc4_8c_source.html
// @NUL0x4C | @mrd0x : MalDevAcademy
// uncomment below for windows
// #include <Windows.h>
#include "deploy_rc4.h"

unsigned char shellcode[] = {"This is the shellcode that is used for rc4 encryption !"};
unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

void rc4Init(Rc4Context *context, const unsigned char *key, size_t length)
{
    unsigned int i;
    unsigned int j;
    unsigned char temp;

    // Check parameters
    if (context == NULL || key == NULL)
    {
        fprintf(stderr, "Invalid parameters!\n");
        exit(ERROR_INVALID_PARAMETER);
    }

    // Clear context
    context->i = 0;
    context->j = 0;

    // Initialize the S array with identity permutation
    for (i = 0; i < BUF_MAX; i++)
    {
        context->arr[i] = i;
    }

    // S is then processed for BUF_MAX iterations
    for (i = 0, j = 0; i < BUF_MAX; i++)
    {
        // Randomize the permutations using the supplied key
        j = (j + context->arr[i] + key[i % length]) % BUF_MAX;

        // Swap the values of arr[i] and arr[j]
        temp = context->arr[i];
        context->arr[i] = context->arr[j];
        context->arr[j] = temp;
    }
}

void rc4Cipher(Rc4Context *context, const unsigned char *input, unsigned char *output, size_t length)
{
    unsigned char temp;

    // Restore context
    unsigned int i = context->i;
    unsigned int j = context->j;
    unsigned char *arr = context->arr;

    // Encryption loop
    while (length > 0)
    {
        // Adjust indices
        i = (i + 1) % BUF_MAX;
        j = (j + arr[i]) % BUF_MAX;

        // Swap the values of arr[i] and arr[j]
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        // If the input and output are valid
        if (input != NULL && output != NULL)
        {
            // XOR the input data with the RC4 stream
            *output = *input ^ arr[(arr[i] + arr[j]) % BUF_MAX];

            // Increment data pointers
            input++;
            output++;
        }

        // Remaining bytes to process
        length--;
    }

    // Save context
    context->i = i;
    context->j = j;
}

int main()
{
    unsigned char *Ciphertext = (unsigned char *)malloc(sizeof(shellcode) * sizeof(int));
    unsigned char *PlainText = (unsigned char *)malloc(sizeof(shellcode) * sizeof(int));
    Rc4Context ctx = {0};
    // Intializing the struct
    rc4Init(&ctx, key, sizeof(key));

    // Encryption
    rc4Cipher(&ctx, shellcode, Ciphertext, sizeof(shellcode));

    printf("[i] Ciphertext : 0x%s \n", Ciphertext);
    printf("[#] Press <Enter> To Decrypt...");
    getchar();

    rc4Init(&ctx, key, sizeof(key));

    // Decryption
    rc4Cipher(&ctx, Ciphertext, PlainText, sizeof(shellcode));

    printf("[i] PlainText : \"%s\" \n", (char *)PlainText);
    printf("[#] Press <Enter> To Quit ...");
    getchar();

    // free allocated memory
    free(Ciphertext);
    free(PlainText);
    return 0;
}
// Hint: can get rid of redundant codes via usage of malloc/calloc

/* End of file */
