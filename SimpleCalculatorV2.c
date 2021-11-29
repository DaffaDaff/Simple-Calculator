#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char str[500];
int lenght;

int findDigitFromString(char nStr[], int startIndex)
{
    int dit;
    int len = strlen(nStr);
    for (int i = 0, j = startIndex; i <= len; i++, j++)
    {
        if(!(nStr[j] >= 48 && nStr[j] <= 57) || !nStr[j] == '-')
        {
            dit = i;
            break;
        }
    }
    
    return dit;
}

// Remove String Element
// Remove element in an index of a string
const char * removeStrElement(char nStr[], int *len, int index)
{
    for(int i = index; i < *len; i++)
    {
        nStr[i] = nStr[i + 1];
    }
    
    *len--;
    
    return nStr;
}

// Insert String Element
// Insert element in an index of a string
const char * insertStrElement(char nStr[], int *len, int index, char value)
{
    
    for(int i = *len; i >= index; i--)
    {
        if(i == index) nStr[i] = value;
        else nStr[i] = nStr[i - 1];
    }
    if(*len == index) nStr[index] = value;
    
    *len += 1;
    

    return nStr;
}

// Insert String Element
// Insert element in an index of a string
const char * insertStrElementWithInt(char nStr[], int *len, int index, int value)
{
    char intStr[*len];
    sprintf(intStr, "%d", value);
    
    for (int i = index, j = 0; j < findDigitFromString(intStr, 0); i++, j++)
    {
        insertStrElement(nStr, &*len, i, intStr[j]);
    }
    
    return nStr;
}

// Remove Spaces
// Remove Spaces from a string
const char * removeSpaces(char nStr[], int *len)
{
    for(int i = 0; i < *len; i++)
    {
        if (nStr[i] == ' ')
        {
            removeStrElement(nStr, &*len, i); 
        }
    }
    
    return nStr;
}

//Validation
// This funcion validate symbols and format
// current valid symbol is: '+', '-'
//
// format should look like this:
// <Number><Space><Operator><Space><Number><Space><Operator>...
int Validate(char nStr[], int len)
{
    int isSpace = 0; // 0 is non space, 1 is space
    int state = 0; // state 0 is number, state 1 is operator
    int parenthesisCount; // counter for parenthesis, +1 if '(' and -1 if ')'. by the end of validation, this value should be 0
    
    for(int i = 0; i < len; i++)
    {
        if(isSpace)
        {
            isSpace = 0;
            
            if(nStr[i] == ' ')
                continue;
            else 
            {
                printf("ERROR: Invalid Spacing");
                return 0;
            }
        }
        else
        {
            isSpace = 1;
            
            if(state == 0)
            {
                // Parenthesis check
                if (nStr[i] == '(')
                {
                    parenthesisCount++;
                    continue;
                }
                
                state = 1;
                
                //Number check
                if(nStr[i] >= 48 && str[i] <= 57)
                {
                    // check if there is still number after this (more digit)
                    if(nStr[i + 1] >= 48 && nStr[i] <= 57)
                    {
                        state = 0;
                        isSpace = 0;
                    }
                    
                    continue;
                }
                else if(nStr[i] == ' ')
                {
                    printf("ERROR: Invalid Spacing");
                    return 0;
                }
                else 
                {
                    printf("ERROR: Invalid Number");
                    return 0;
                }
            }
            else if (state == 1)
            {
                // Parenthesis check
                if(nStr[i] == ')')
                {
                    parenthesisCount--;
                    continue;
                }
                
                state = 0;
                
                // Operator check
                switch (nStr[i])
                {
                    case ' ':
                        printf("ERROR: Invalid Spacing");
                        return 0;
                    case '+':
                        continue;
                    case '-':
                        continue;
                    case '*':
                        continue;
                    case '/':
                        continue;
                    case '^':
                        continue;
                    default:
                        printf("ERROR: Unknown Operator");
                        return 0;
                }
            }
        }
    }
    
    return 1;
}

const char * PowCalculation(char nStr[], int len, int index)
{
    //printf(" %d ", index);
    for (int i = index; i < len; i++)
    {
        if(nStr[i] == '^')
        {
            while(nStr[i - 1] >= '0' && nStr[i - 1] <= '9')
                i--;
            
            int index1 = i;
            int digit1 = findDigitFromString(nStr, i);
            int n1;
            
            char intStr1[digit1];
            for(int j = 0; j < digit1; j++, i++)
                intStr1[j] = nStr[i];
            
            n1 = atoi(intStr1);
            
            i++;
            
            int index2 = i;
            int digit2 = findDigitFromString(nStr, i);
            int n2;
            
            if(nStr[i + digit2] == '^')
            {
                PowCalculation(nStr, len, i);
                digit2 = findDigitFromString(nStr, i);
            }
            
            char intStr2[digit2];
            for(int j = 0; j < digit2; j++, i++)
                intStr2[j] = nStr[i];
            
            n2 = atoi(intStr2);
            
            for(int k = 0; k <= digit1 + digit2; k++)
            {
                
                removeStrElement(nStr, &len, index1);
            }
            
            int n = pow(n1, n2);
            
            insertStrElementWithInt(nStr, &len, index1, n);
            
            i = index;
        }
    }
    
    return nStr;
}

const char * MultDivCalculation(char nStr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if(nStr[i] == '*' || nStr[i] == '/')
        {
            int mode;
            if(nStr[i] == '*')
                mode = 0;
            else if(nStr[i] == '/')
                mode = 1;
            
            while(nStr[i - 1] >= '0' && nStr[i - 1] <= '9')
                i--;
            
            int index1 = i;
            int digit1 = findDigitFromString(nStr, i);
            int n1;
            
            char intStr1[digit1];
            for(int j = 0; j < digit1; j++, i++)
                intStr1[j] = nStr[i];
            
            n1 = atoi(intStr1);
            
            i++;
            
            int index2 = i;
            int digit2 = findDigitFromString(nStr, i);
            int n2;
            
            
            char intStr2[digit2];
            for(int j = 0; j < digit2; j++, i++)
                intStr2[j] = nStr[i];
            
            n2 = atoi(intStr2);
            
            for(int k = 0; k <= digit1 + digit2; k++)
            {
                
                removeStrElement(nStr, &len, index1);
            }
            
            int n;
            if(mode == 0)
                n = n1 * n2;
            else if(mode == 1)
                n = n1 / n2;
            
            insertStrElementWithInt(nStr, &len, index1, n);
            
            i = 0;
        }
    }
    
    return nStr; 
}

const char * AddSubtractCalculation(char nStr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if(nStr[i] == '+' || nStr[i] == '-')
        {
            int mode;
            if(nStr[i] == '+')
                mode = 0;
            else if(nStr[i] == '-')
                mode = 1;
            
            while(nStr[i - 1] >= '0' && nStr[i - 1] <= '9')
                i--;
            
            int index1 = i;
            int digit1 = findDigitFromString(nStr, i);
            int n1;
            
            char intStr1[digit1];
            for(int j = 0; j < digit1; j++, i++)
                intStr1[j] = nStr[i];
            
            n1 = atoi(intStr1);
            
            i++;
            
            int index2 = i;
            int digit2 = findDigitFromString(nStr, i);
            int n2;
            
            
            char intStr2[digit2];
            for(int j = 0; j < digit2; j++, i++)
                intStr2[j] = nStr[i];
            
            n2 = atoi(intStr2);
            
            for(int k = 0; k <= digit1 + digit2; k++)
            {
                
                removeStrElement(nStr, &len, index1);
            }
            
            int n;
            if(mode == 0)
                n = n1 + n2;
            else if(mode == 1)
                n = n1 - n2;
            
            insertStrElementWithInt(nStr, &len, index1, n);
            
            i = 0;
        }
    }
    
    return nStr; 
}

int Calculate(char nStr[], int len)
{
    removeSpaces(nStr, &len);
    
    PowCalculation(nStr, len, 0);
    MultDivCalculation(nStr, len);
    AddSubtractCalculation(nStr, len);
    
    puts(nStr);
}

void start()
{
    printf("Enter Operation: \n");
    scanf("%[^\n]s", str);
    
    lenght = strlen(str);
    
    if(!Validate(str, lenght)) 
        return;

    Calculate(str, lenght);
}

int main()
{
    start();
    
    return 0;
}




