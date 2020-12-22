#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Declaring functions */
bool isAlpha(char c);
bool isSent(char c);

/* Main function */
int main(void)
{
    /* Get user text input */
    string text=get_string("Text: ");
    /* Initialize and declare variables for words, letters, and sentences */
    int lett=0;
    int sent=0;
    int words=1;
    /* For loop to check each character */
    for (int i=0; i<strlen(text); i++)
    {
        if (isAlpha(text[i])==true)
        {
            lett++;
        }
        else if (isSent(text[i])==true)
        {
            sent++;
        }
        else if(text[i]==' ')
        {
            words++;
        }
    }
    /* Use the Coleman-Liau formula to calculate readability */
    float index = 0.0588 * ((float)lett/(float)words*100) - 0.296 * ((float)sent/(float)words*100) - 15.8;
    int gradeLev=round(index);

    /* Print final grade level */
    if (index<1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index>=16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", gradeLev);
    }
    return 0;
}

/* Functions to find all the is the character is a character */
bool isAlpha(char c)
{
    if((c>64 && c<91) || (c>96 && c<123))
    {
        return true;
    }
    return false;
}

bool isSent(char c)
{
    if (c=='.'|| c=='?'||c=='!')
    {
        return true;
    }
    return false;
}