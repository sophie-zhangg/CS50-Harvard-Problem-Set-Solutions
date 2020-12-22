#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/*Declare the function */
void encrypt(string message, string key);

/* Main function */
int main(int argc, string argv[])
{
    /* Check if command-line has one arguent */
    if (argc == 2)
    {
        /* Take in the input from the command-line*/
        string text = argv[1];
        /* Check if key has 26 characters */
        if (strlen(text) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        /* Check each character if it is not a letter */
        for (int i = 0; i < 26; i++)
        {
            if (((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123)) == false)
            {
                printf("ERROR: Use letters in the key, not any other characters\n");
                return 1;
            }
            /* Nested loop to check if there are repeated letters */
            for (int j = i + 1; j < 26; j++)
            {
                if (text[i] == text[j])
                {
                    printf("ERROR: Key has repeat letters\n");
                    return 1;
                }
            }
        }
        /* Input your plain text*/
        string plain_text = get_string("plaintext: ");
        /* Print the plain text as cipher text/calling the function */
        encrypt(plain_text, text);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
/* Encrypt my message with this void function, inputs the message and the key, prints the string cipher text*/
void encrypt(string message, string key)
{
    /* Declare local variables */
    int numKey[26];
    int val;
    int length = strlen(message);
    /* Create char array for the cipher */
    char cipher[length + 1];
    cipher[length] = '\0';
    /* Convert the key into a int array so that case in the key doesn't matter */
    for (int i = 0; i < 26; i++)
    {
        if (key[i] > 64 && key[i] < 91)
        {
            val = key[i] - 65;
        }
        else
        {
            val = key[i] - 97;
        }
        numKey[i] = val;
    }
    /* Convert the message into the cipher text. Avoiding changing the character if it is not a letter*/
    for (int i = 0; i < length; i++)
    {
        if (message[i] > 64 && message[i] < 91)
        {
            cipher[i] = (char)(numKey[message[i] - 65] + 65);
        }
        else if (message[i] > 96 && message[i] < 123)
        {
            cipher[i] = (char)(numKey[message[i] - 97] + 97);
        }
        else
        {
            cipher[i] = message[i];
        }
    }
    /* Print the cipher text */
    printf("ciphertext: %s\n", cipher);
}