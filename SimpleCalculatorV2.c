#include <stdio.h>
#include <string.h>
#include <math.h>

char str[500];
int lenght;

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

// Remove Spaces
// Remove Spaces from a string
const char * removeSpaces(char nStr[], int len)
{
    for(int i = 0; i < len; i++)
    {
        if (nStr[i] == ' ')
            removeStrElement(nStr, &len, i);
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

void start()
{
    printf("Enter Operation: \n");
    scanf("%[^\n]s", str);
    
    lenght = strlen(str);
    
    if(!Validate(str, lenght)) 
        return;
    
    removeSpaces(str, lenght);
}

int main()
{
    start();
    
    return 0;
}
