#include <stdio.h>
#include "input.h"

int getInteger(char *msg ,int min, int max)
{
    int n;
    while(1)
    {
        printf("%s",msg);
        if((scanf("%d",&n))!= 1 && n>=min && n<=max)
        {
            return n;
        }

        printf("Invalid Input! Enter An Integer: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Integer
    }

}

float getFloating(char *msg ,int min, int max)
{
    float n;
    while(1)
    {
        printf("%s",msg);
        if((scanf("%f",&n))!= 1 && n>=min && n<=max)
        {
            return n;
        }
        
        printf("Invalid Input! Enter A Float: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Float
    }
}