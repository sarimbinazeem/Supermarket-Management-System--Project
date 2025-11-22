#include <stdio.h>
#include "input.h"

//--------Input Validator For Integers----------
int getInteger(char *msg ,int min, int max)
{
    int n;
    while(1)
    {
        //Print Initial Message
        printf("%s",msg);
        //Check IF THE number is Integer and In RANGE
        if((scanf("%d",&n))!= 1 && n>=min && n<=max)
        {
            return n;
        }

        printf("Invalid Input! Enter An Integer: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Integer
    }

}

//----------Input Validator For Floating Numbers----------
float getFloating(char *msg ,int min, int max)
{
    float n;
    while(1)
    {
        //Prints Initial Message
        printf("%s",msg);
        //Checks If The Number Is In Range And A Float Number
        if((scanf("%f",&n))!= 1 && n>=min && n<=max)
        {
            return n;
        }
        
        printf("Invalid Input! Enter A Float: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Float
    }
}