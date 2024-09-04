#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT 1000
char encrypt_char(char plain_char, char key_char) {
    if (isupper(plain_char)) {
        return 'A' + (plain_char - 'A' + (toupper(key_char) - 'A')) % 26;
    } else if (islower(plain_char)) {
        return 'a' + (plain_char - 'a' + (tolower(key_char) - 'a')) % 26;
    } else {
        return plain_char;
    }
}

void polyalphabetic_encrypt(char *plaintext, char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {
        ciphertext[i] = encrypt_char(plaintext[i], key[i % key_len]);
    }
    ciphertext[text_len] = '\0';
}

int main() {
    char plaintext[MAX_TEXT];
    char key[MAX_TEXT];
    char ciphertext[MAX_TEXT];
    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_TEXT, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
	printf("Enter the key: ");
    fgets(key, MAX_TEXT, stdin);
    key[strcspn(key, "\n")] = '\0';
    polyalphabetic_encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

