#include <stdio.h>
#include <ctype.h>
#include <string.h>
void encrypt(char *plaintext, const char *key) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            plaintext[i] = isupper(c) ? key[c - 'A'] : tolower(key[c - 'a']);
        }
    }
}
void decrypt(char *ciphertext, const char *key) {
    int length = strlen(ciphertext);
    char reverseKey[26];

    for (int i = 0; i < 26; i++) {
        reverseKey[key[i] - 'A'] = i + 'A';
    }

    for (int i = 0; i < length; i++) {
        char c = ciphertext[i];

        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            ciphertext[i] = isupper(c) ? reverseKey[c - 'A'] : tolower(reverseKey[c - 'a']);
        }
    }
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    const char key[] = "QWERTYUIOPLKJHGFDSAZXCVBNM"; 
    printf("Enter the text to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    strcpy(ciphertext, plaintext);
    encrypt(ciphertext, key);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, key);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

