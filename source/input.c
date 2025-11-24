#include <stdio.h>
#include "input.h"

//--------Input Validator For Integers----------
int getInteger(char *msg ,int min, int max)
{
    int n;
    while(1)
    {
        //Print Initial Message
        printf("%s", msg);
        if (scanf("%d", &n) != 1)  // First check if the input is an integer
        {
            printf("Invalid Input! Enter An Integer: ");
            while (getchar() != '\n');  //To Clear Buffer If A Person Adds a String instead of An Integer
        }
        else if (n >= min && n <= max)  // Then check the range
        {
            return n;
        }
        else
        {
            printf("Invalid input! Enter an integer between %d and %d: ", min, max);
        }
    }
}

//----------Input Validator For Floating Numbers----------
float getFloating(char *msg ,float min, float max)
{
    float n;
    while(1)
    {
        //Print Initial Message
        printf("%s", msg);
        if (scanf("%f", &n) != 1)  // First check if the input is an float
        {
            printf("Invalid Input! Enter A Float: ");
            while (getchar() != '\n');  //To Clear Buffer If A Person Adds a String instead of A Float
        }
        else if (n >= min && n <= max)  // Then check the range
        {
            return n;
        }
        else
        {
            printf("Invalid input! Enter a float between %.2f and %.2f: ", min, max);
        }
    }
}