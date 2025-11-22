#include <stdio.h>
#include "input.h"

int getInteger()
{
    int n;
    while((scanf("%d",&n))!= 1)
    {
        printf("Invalid Input! Enter An Integer: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Integer
    }

    return n;
}

int getFloating()
{
    int n;
    while((scanf("%f",&n))!= 1)
    {
        printf("Invalid Input! Enter Valid Price: ");
        while(getchar() ! = '\n'); //To Clear Buffer If A Person Adds a String instead of An Integer
    }

    return n;
}