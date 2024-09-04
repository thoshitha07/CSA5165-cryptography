#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 5
void prepareMatrix(char matrix[SIZE][SIZE], const char *key) {
    int used[26] = {0};
    int k = 0, x = 0, y = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'J') key[i] = 'I'; 
        if (!used[key[i] - 'A']) {
            matrix[x][y++] = key[i];
            used[key[i] - 'A'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }

    // Fill the remaining matrix with the rest of the alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; // Skip 'J'
        if (!used[c - 'A']) {
            matrix[x][y++] = c;
            used[c - 'A'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}
void prepareText(char *text) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') text[i] = 'I';
    }
    for (int i = 0; i < length; i += 2) {
        if (text[i] == text[i + 1]) {
            memmove(&text[i + 2], &text[i + 1], length - i);
            text[i + 1] = 'X';
            length++;
        }
    }

    if (length % 2 != 0) {
        text[length] = 'X';
        text[length + 1] = '\0';
    }
}

void findPosition(char matrix[SIZE][SIZE], char c, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[SIZE][SIZE], char *first, char *second) {
    int row1, col1, row2, col2;
    findPosition(matrix, *first, &row1, &col1);
    findPosition(matrix, *second, &row2, &col2);

    if (row1 == row2) {
        *first = matrix[row1][(col1 + 1) % SIZE];
        *second = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *first = matrix[(row1 + 1) % SIZE][col1];
        *second = matrix[(row2 + 1) % SIZE][col2];
    } else {
        *first = matrix[row1][col2];
        *second = matrix[row2][col1];
    }
}

void encryptPlayfair(char *text, char matrix[SIZE][SIZE]) {
    for (int i = 0; text[i] != '\0'; i += 2) {
        encryptPair(matrix, &text[i], &text[i + 1]);
    }
}
int main() {
    char key[100], plaintext[100];
    char matrix[SIZE][SIZE];
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    prepareMatrix(matrix, key);
    prepareText(plaintext);
    printf("Prepared text: %s\n", plaintext);
    encryptPlayfair(plaintext, matrix);
    printf("Encrypted text: %s\n", plaintext);
    return 0;
}

