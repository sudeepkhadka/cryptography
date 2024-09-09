#include <openssl/rc4.h>
#include <stdio.h>
#include <string.h>

#define OSSL_DEPRECATEDIN_3_0

int main()
{
    // Key and input data (plaintext)
    unsigned char key[] = "SuperSecretKey";                 // RC4 key (you can modify this as needed)
    unsigned char plaintext[] = "This is a secret message"; // Message to be encrypted
    unsigned char ciphertext[128];                          // Buffer for ciphertext
    unsigned char decryptedtext[128];                       // Buffer for decrypted text

    // RC4 key structure
    RC4_KEY rc4_key;

    // Initialize the RC4 key
    RC4_set_key(&rc4_key, strlen((const char *)key), key);

    // Encrypt the plaintext
    RC4(&rc4_key, strlen((const char *)plaintext), plaintext, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < strlen((const char *)plaintext); i++)
    {
        printf("%02x ", ciphertext[i]); // Print the ciphertext in hexadecimal
    }
    printf("\n");

    // Reset the key to decrypt (RC4 is a symmetric cipher)
    RC4_set_key(&rc4_key, strlen((const char *)key), key);

    // Decrypt the ciphertext
    RC4(&rc4_key, strlen((const char *)plaintext), ciphertext, decryptedtext);
    decryptedtext[strlen((const char *)plaintext)] = '\0'; // Null-terminate the string

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
