#include <stdio.h>
#include <string.h>
#include <ctype.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void affineDecrypt(char* ciphertext, char* plaintext, int a, int b) {
    int a_inv = modInverse(a, 26);
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
            plaintext[i] = ciphertext[i]; // Non-alphabet characters remain unchanged
        }
        i++;
    }
    plaintext[i] = '\0';
}
int main() {
    char ciphertext[1000];
    char plaintext[1000];
    int a, b;
    char y1 = 'B';  
    char y2 = 'U';  
    char x1 = 'E';  
    char x2 = 'T';  
    int y1_idx = y1 - 'A';
    int y2_idx = y2 - 'A';
    int x1_idx = x1 - 'A';
    int x2_idx = x2 - 'A';
    int a_inv = modInverse((x1_idx - x2_idx + 26) % 26, 26);
    if (a_inv == -1) {
        printf("Cannot break the cipher: no modular inverse for the difference between the letter indices.\n");
        return 1;
    }
    a = (a_inv * (y1_idx - y2_idx + 26)) % 26;
    b = (y1_idx - a * x1_idx + 26) % 26;
    printf("Possible values for a and b are: a = %d, b = %d\n", a, b);
    printf("Enter the ciphertext: ");
    fgets(ciphertext, 1000, stdin);
    size_t len = strlen(ciphertext);
    if (len > 0 && ciphertext[len - 1] == '\n') {
        ciphertext[len - 1] = '\0';
    }
    affineDecrypt(ciphertext, plaintext, a, b);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}

