#include <stdio.h>

// Get Length
// Function to get length of a string
// from start to end of char
int getLength(char str[])
{
    for(int i = 0; i < 500; i++)
    {
        if(str[i] == 0) 
        {
            return i;
        }
    }
}

// Char to int
// convert integer char ('0', '1', ..., '8', '9') to integer (0, 1, ..., 8, 9)
int char2int(char c)
{
    return c - 48;
}

//Validation
// This funcion validate symbols and format
// current valid symbol is: '+', '-'
//
// format should look like this:
// <Number><Space><Operator><Space><Number><Space><Operator>...
int validate(char str[], int len)
{
    int isSpace = 0; // 0 is non space, 1 is space
    int state = 0; // state 0 is number, state 1 is operator
    
    for(int i = 0; i < len; i++)
    {
        if(isSpace)
        {
            isSpace = 0;
            
            if(str[i] == ' ')
            {
                continue;
            }
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
                state = 1;
                
                if(str[i] >= 48 && str[i] <= 57)
                {
                    if(str[i + 1] >= 48 && str[i] <= 57)
                    {
                        state = 0;
                        isSpace = 0;
                    }
                    
                    continue;
                }
                else if(str[i] == ' ')
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
                state = 0;
                
                switch (str[i])
                {
                    case ' ':
                        printf("ERROR: Invalid Spacing");
                        return 0;
                    case '+':
                        continue;
                    case '-':
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

// Calculation
int calculation(char str[], int len)
{
    int array2sum[len];
    
    int arrIndex = 0;
    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 48 && str[i] <= 57)
        {
            int n = char2int(str[i]);
            
            if(str[i - 2] == '-')
            {
                n *= -1;
            }
            
            array2sum[arrIndex] = n;
            
            arrIndex++;
        }
    }
    
    int sum;
    for(int i = 0; i < len; i++)
    {
        sum += array2sum[i];
    }
    
    printf("%d", sum);
    return sum;
}

int main()
{
    char str[500];
    int len;
    
    scanf("%[^\n]s", str);
    
    len = getLength(str);
    
    if( !validate(str, len) ) return -1;
    
    calculation(str, len);
    
    return 0;
}

