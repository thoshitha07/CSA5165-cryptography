#include <stdio.h>
#include <string.h>
#include <ctype.h>
int isCoprime(int a, int m) {
    while (m != 0) {
        int temp = m;
        m = a % m;
        a = temp;
    }
    return (a == 1);
}
void affineEncrypt(char* plaintext, char* ciphertext, int a, int b) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - offset) + b) % 26) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0';
}
void affineDecrypt(char* ciphertext, char* plaintext, int a, int b) {
    int a_inv = -1;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }

    if (a_inv == -1) {
        printf("Decryption not possible, as modular inverse does not exist.\n");
        return;
    }
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((a_inv * (ciphertext[i] - offset - b + 26)) % 26) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}
int main() {
    char plaintext[1000];
    char ciphertext[1000];
    int a, b;
    printf("Enter the plaintext: ");
    fgets(plaintext, 1000, stdin);
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }
    printf("Enter the values of a and b for the Affine cipher (a and b are keys):\n");
    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    if (!isCoprime(a, 26)) {
        printf("The value of 'a' must be coprime with 26 for the cipher to be one-to-one.\n");
        return 1;
    }
    affineEncrypt(plaintext, ciphertext, a, b);
    printf("Encrypted text: %s\n", ciphertext);
    affineDecrypt(ciphertext, plaintext, a, b);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}

