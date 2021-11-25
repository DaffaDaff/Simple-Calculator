#include <stdio.h>


//Print Array
void printArray(int arr[], int len)
{
    printf("{");
    for(int i = 0; i < len; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("}");
}

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

// Power
int pwr(int n, int p)
{
    int result = 1;
    
    for(int i = 0; i < p; i++)
    {
        result *= n;
    }
    
    return result;
}

// Char to Integer
// convert integer char ('0', '1', ..., '8', '9') to integer (0, 1, ..., 8, 9)
int char2int(char c)
{
    if((int)c >= 48 && (int)c <= 57)
        return c - 48;
}

// String to Integer
// convert integer string ("1", "23", "456", etc) to integer (1, 23, 456, etc)
int str2int(char str[])
{
    int len = getLength(str);
    
    int result = 0;
    for(int i = 0, j = 0; i <= len; i++)
    {
        if(str[len - i] >= 48 && str[len - i] <= 57){
            
            result += char2int(str[len - i]) * pwr(10, j);
            j++;
        }
        else
            continue;
    }
    
    return result;
}

// Clear String
// assign all char to 0
const char * clearString(char str[], int len)
{
    for(int i = 0; i < len; i++)
    {
        str[i] = 0;
    }
    
    return str;
}

// Clear Array
// assign all value to 0
const int * clearArray(int arr[], int len)
{
    for(int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }
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
//
// How it works:
// 1. every number in string will be converted into integer
// 2. number will be stored in sum array
// 3. all value in array will be summed
int calculation(char str[], int len)
{
    int sumArray[len];
    clearArray(sumArray, len); // Clear array value to zero
    
    int arrIndex = 0;
    
    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 48 && str[i] <= 57)
        {
            int index = i; // define index where the number start
            
            // Find how many digit in the number
            int digit;
            for (int j = 0, k = i; j <= len; j++, k++)
            {
                if(!(str[k] >= 48 && str[k] <= 57))
                {
                    digit = j;
                    break;
                }
            }
            
            // string for number
            // adding digits in number into string and convert string into integer
            char nStr[digit];
            clearString(nStr, digit);
            
            // Write every integer char into string until space
            for (int j = 0; j <= digit; j++, i++)
            {
                if(str[i] >= 48 && str[i] <= 57)
                {
                    nStr[j] = str[i];
                }
                else 
                {
                    nStr[j] = 0;
                }
            }
            
            int n = str2int(nStr); // Convert integer string to integer
            
            // negate value if '-' is present before number
            if(str[index - 2] == '-')
            {
                n *= -1;
            }
            
            // add number into previous sum
            sumArray[arrIndex] += n;
            arrIndex++;
        }
    }
    
    // Sum every value in the sumArray
    int sum = 0;
    
    for(int i = 0; i < len; i++)
    {
        sum += sumArray[i];
    }
    
    return sum;
}

int main()
{
    char str[500];
    int len;
    
    scanf("%[^\n]s", str);
    
    len = getLength(str);
    
    if( !validate(str, len) ) return -1;
    
    printf("%d", calculation(str, len));
    
    return 0;
}
