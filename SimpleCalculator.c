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

// Find Digit
// Find how many digit in input string number
int findDigit(char str[], int startIndex)
{
    int dit;
    int len = getLength(str);
    for (int i = 0, j = startIndex; i <= len; i++, j++)
    {
        if(!(str[j] >= 48 && str[j] <= 57))
        {
            dit = i;
            break;
        }
    }
    
    return dit;
}

// Find Integer From string
// Find number from string starting from startIndex
int intFromString(char str[], int startIndex, int digit)
{
    char nStr[digit];
    clearString(nStr, digit);
            
    // Write every integer char into string
    for (int j = 0, i = startIndex; j <= digit; j++, i++)
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
    
    return str2int(nStr); // Convert integer string to integer
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
                    case '*':
                        continue;
                    case '/':
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

// Multiplication & Division Calculation
//
// Calculate multiplication and division from a string
// 
int MultDivCalculation(char str[], int len)
{
    int result = 1;
    
    // Start calculating Mult/Div sequence
    for(int i = 0; i <= len; i++)
    {
        if(str[i] >= 48 && str[i] <= 57)
        {
            int index = i;
            
            // Convert the string number into integer
            int digit;
            digit = findDigit(str, index);
            
            i += digit;
            
            int n = intFromString(str, index, digit);
            
            
            
            if(index <= 1) result = n;
            else if(str[index - 2] == '*')
                result *= n;
            else if(str[index - 2] == '/')
                result /= n;
        }
    }
    
    return result;
}

// Calculation
//
// How it works:
// 1. check if operator after number is multiplication or division, if yes then mult/div sequences will calculated first in another function
// 2. every number in string will be converted into integer
// 3. number will be stored in sum array
// 4. all value in array will be summed
int calculation(char str[], int len)
{
    int sumArray[len];
    clearArray(sumArray, len); // Clear array value to zero
    
    int arrIndex = 0;
    
    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 48 && str[i] <= 57)
        {
            int n;
            int index = i; // define index where the number start
            
            // Find how many digit in the number
            int digit;
            digit = findDigit(str, index);
            
            // Multiplication & Division Check
            if(str[i + digit + 1] == '*' || str[i + digit + 1] == '/')
            {
                // string of Mult/Div sequence
                char nStr[len];
                clearString(nStr, len);
                
                int length;
                
                // Write sequence from main string
                for(int j = 0; i < len; j++, i++)
                {
                    // Stop when there is addition/subtraction
                    if( str[i] == '+' || str[i] == '-')
                    {
                        break;
                    }
                    
                    nStr[j] = str[i]; // Write every char into string sequnce
                    length = j;
                }
                
                // Start Calculation
                n = MultDivCalculation(nStr, length);
            }
            // Addition & Subtraction
            else {
                i += digit;
                
                n = intFromString(str, index, digit);
            }
            
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
