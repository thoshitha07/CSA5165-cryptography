#include <stdio.h>
#include <ctype.h>
#include <string.h>
void caesarCipher(char* text, int k) 
{
    int length = strlen(text);
    for (int i = 0; i < length; i++) 
	{
        char c = text[i];
        if (isalpha(c)) 
		{
            char offset = isupper(c) ? 'A' : 'a';
            c = ((c - offset + k) % 26) + offset;
        }
        text[i] = c; 
    }
}
int main() 
{
    char text[100];
    int k;
    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter the key (k) value (1-25): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid key value! It should be in the range 1 through 25.\n");
        return 1;
    }
    caesarCipher(text, k);
    printf("Encrypted text: %s\n", text);

    return 0;
}

