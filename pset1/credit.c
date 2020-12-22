#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Declaring functions
int checksum(long card);
int getdigit(long num, int n);

int main(void)
{
    //get a long int
    long cardNum = get_long("Number: ");
    int numOfDigits;
    //check if right number of digits and save the number for later use
    if (cardNum>=1000000000000 && cardNum<10000000000000)
    {
        numOfDigits=13;
    }
    else if (cardNum>=100000000000000 && cardNum<1000000000000000)
    {
        numOfDigits=15;
    }
    else if (cardNum>=1000000000000000 && cardNum<10000000000000000)
    {
        numOfDigits=16;
    }
    //if not right number of digits, card is invalid
    else
    {
        printf("INVALID\n");
        return 0;
    }
    //use check sum to find out if valid
    int sum=checksum(cardNum);
    //find the first two digits to identify which credit card structure
    int firsttwo=getdigit(cardNum, numOfDigits)*10+getdigit(cardNum, numOfDigits-1);
    //check for credit card company and correct num of digits
    if (sum%10==0) {
        if ((firsttwo==34 || firsttwo==37) && numOfDigits==15)
        {
            printf("AMEX\n");
            return 0;
        }
        else if ((firsttwo>50 && firsttwo<56) && numOfDigits==16)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if (firsttwo/10==4 && (numOfDigits==13 || numOfDigits==16))
        {
            printf("VISA\n");
            return 0;
        }
        //if structure does not match, it is invalid
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else {
        printf("INVALID\n");
        return 0;
    }
}
//check sum function:
int checksum(long card)
{
    int sum=0;
    int current;
    int numOfDigits;
    if (card>=1000000000000 && card<10000000000000)
    {
        numOfDigits=13;
    }
    else if (card>=100000000000000 && card<1000000000000000)
    {
        numOfDigits=15;
    }
    else {
        numOfDigits=16;
    }
    int counter=1;
    do
    {
        current=getdigit(card, counter);
        if (counter%2==0)
        {
            current*=2;
            if (current>9)
            {
                current=getdigit(current, 1)+getdigit(current,2);
            }

        }
        sum+=current;
        counter++;
    }
    while (counter<numOfDigits+1);
    return sum;
}
//function to get a digit from a number
int getdigit(long num, int n)
{
    long answer;
    if (n==1)
    {
        return num%10;
    }
    answer=(long)(num/pow(10,(n-1)))%10;
    return answer;
}
