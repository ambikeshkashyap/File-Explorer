#include <iostream>
#include "string.h"

int kmp_isSubStringPresent(char *superString,char *subString,int *lps)
{
    for(int superCounter = 0,subCounter = -1;superString[superCounter];)
    {
        if(superString[superCounter] == getLower(subString[subCounter + 1]) ||
           superString[superCounter] == getUpper(subString[subCounter + 1]) )
        {
            superCounter++;
            subCounter++;
            if('\0' == subString[subCounter + 1])
            {
                return superCounter - subCounter - 1;
            }
        }
        else if(-1 == subCounter)
        {
            superCounter++;
        }
        else
        {
            subCounter = lps[subCounter] - 1;
        }
    }
    return -1;
}

void calculate_LPS(char *str,int *lps,int size)
{
    if('\0' != *str)
    {
        int patLen = 0;
        lps[0] = 0;
        for(int counter = 1;counter < size;)
        {
            if(str[counter] == str[patLen])
            {
                patLen++;

                lps[counter++] = patLen;
            }
            else
            {
                if(0 != patLen)
                {
                    patLen = lps[patLen - 1];
                }
                else
                {
                    lps[counter++] = 0;
                }
            }
        }
    }
    return;
}

///Naive Algorithm(Basic Algorithm) O(M*N)
int isSubStringPresent(char *str,char *subStr)
{
    int strCounter = 0,subStrCounter = 0,temp = 0;
    for(;str[strCounter];strCounter++)
    {
        for(subStrCounter = 0,temp = strCounter;str[temp] && subStr[subStrCounter];subStrCounter++,temp++)
        {
            if(str[temp] != subStr[subStrCounter])
            {
                break;
            }
        }
        if(!subStr[subStrCounter])
        {
            return strCounter;
        }

    }
    return -1;
}

///Copy The Contained Of Source String In Destination String
void stringCopy(char *destination,char *source)
{
    while(*source)
    {
        *destination = *source;
        source++;
        destination++;
    }
    *destination = '\0';

    return;
}

void stringCopy(char *destination,std :: string source)
{
    for(char ch: source)
    {
        *destination = ch;
        destination++;
    }
    *destination = '\0';

    return;
}

/**
    Add Contained Of Second String In First String
    And Return Base Address Of First String
**/
char* stringConcate(char *str1,char *str2)
{
    int counter = 0;
    for(counter = stringLength(str1);*str2;str2++,counter++)
    {
        str1[counter] = *str2;
    }
    str1[counter] = '\0';

    return str1;
}

///Return Length Of String
int stringLength(char *str)
{
    int length = 0;
    const char *temp = str;
    while(*temp)
    {
        temp++;
        length++;
    }
    return length;
}

/**
    Compare Two String
    if String Match Return 0
    otherwise       Return 1
**/
int stringCompare(char *str1,char *str2)
{
    while(*str1 && *str2)
    {
        if(*str1 != *str2)
        {
            return 1;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2 ? 0 : 1;
}

/// It return Lower Case Of Given Character
char getLower(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;
    }

    return ch;
}

/// It return Upper Case Of Given Character
char getUpper(char ch)
{
    if(ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }

    return ch;
}
