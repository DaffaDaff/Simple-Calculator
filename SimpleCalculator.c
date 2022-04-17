/*
Simple Calculator
By Sulthan Daffa Arif Mahmudi

https://github.com/DaffaDaff
*/

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
// you can also use strlen() from <string.h>
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

// Parenthesis Length
// get parenthesis length from a string sequence
int getPrntsLength(char str[], int startIndex, int len)
{
    int lenght = 0;
    
    for(int i = startIndex + 1; i < len; i++)
    {
        if(str[i] == ')') break;
        lenght++;
    }
    
    return lenght;
}

// Power
// Basic Power Calculation
// You can also use pow() from <math.h>
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
// you can also use atoi() from <string.h>
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
int Validate(char str[], int len)
{
    int isSpace = 0; // 0 is non space, 1 is space
    int state = 0; // state 0 is number, state 1 is operator
    int parenthesisCount; // counter for parenthesis, +1 if '(' and -1 if ')'. by the end of validation, this value should be 0
    
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
                // Parenthesis check
                if (str[i] == '(')
                {
                    parenthesisCount++;
                    continue;
                }
                
                state = 1;
                
                //Number check
                if(str[i] >= 48 && str[i] <= 57)
                {
                    // check if there is still number after this (more digit)
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
                // Parenthesis check
                if(str[i] == ')')
                {
                    parenthesisCount--;
                    continue;
                }
                
                state = 0;
                
                // Operator check
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

int Calculation(char str[], int len);

// Power Calculation
//
// Calculate power from a string sequence
// 
int PowCalculation(char str[], int len)
{
    int result = 1;
    
    // array of stored integer number
    int arr[len];
    clearArray(arr, len);
    
    int arrIndex = 0;
    
    for(int i = 0; i <= len; i++)
    {
        int n;
        
        int index = i;
        
        if(str[i] == '(')
        {
            // Parenthesis sequence length
            int length;
            
            length = getPrntsLength(str, i, len);
            
            char prntStr[length];
            clearString(prntStr, length);
            
            // Write sequence inside parenthesis into string (exclude parenthesis symbol)
            i++;
            for(int j = 0; j < length; j++, i++)
            {
                prntStr[j] = str[i];
            }
            i++;
            
            // Calculate string sequence in parenthesis
            n = Calculation(prntStr, length);
            
            // Store integer number n to array
            arr[arrIndex] = n;
            arrIndex++;
        }
        
        if(str[i] >= 48 && str[i] <= 57)
        {
            // Convert the string number into integer
            int digit;
            digit = findDigit(str, index);
            
            i += digit;
            
            n = intFromString(str, index, digit);
            
            // Store integer number n to array
            arr[arrIndex] = n;
            arrIndex++;
        }
    }
    
    // Start calculating pow array
    // calculation start from the end of sequence, because power calculation start from the very top/back
    for(int i = arrIndex - 1; i >= 0; i--)
    {
        result = pwr(arr[i], result);
    }
    
    return result;
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
        int n = 0;
        
        int index = i;
        
        // Check for parenthesis opening
        if(str[i] == '(')
        {
            // Parenthesis sequence length
            int length;
            
            length = getPrntsLength(str, i, len);
            
            char prntStr[length];
            clearString(prntStr, length);
            
            // Write sequence inside parenthesis into string (exclude parenthesis symbol)
            i++;
            for(int j = 0; j < length; j++, i++)
            {
                prntStr[j] = str[i];
            }
            i++;
            
            // Calculate string sequence in parenthesis
            n = Calculation(prntStr, length);
        }
        
        if(str[i] >= 48 && str[i] <= 57)
        {
            // Convert the string number into integer
            int digit;
            digit = findDigit(str, index);
            
            i += digit;
            
            n = intFromString(str, index, digit);
            

        }
        
        if(index <= 1) result = n;
        else if(str[index - 2] == '*')
            result *= n;
        else if(str[index - 2] == '/')
            result /= n;
    }
    
    return result;
}

// Calculation
//
// How it works:
// 1. check every char from the start of the string
// 2. check if there is parenthesis, if yes then parenthesis sequences will be calculated first
// 3. check if operator after number is Power, if yes then pow sequences will be calculated first in another function
// 4. check if operator after number is multiplication or division, if yes then mult/div sequences will be calculated first in another function
// 5. every number in string will be converted into integer
// 6. number will be stored in sum array
// 7. all value in array will be summed
int Calculation(char str[], int len)
{
    int sumArray[len];
    clearArray(sumArray, len); // Clear array value to zero
    
    int arrIndex = 0;
    
    for(int i = 0; i < len; i++)
    {
        int n = 0;
        
        int index = i; // define index where the number start
        
        // Check for parenthesis opening ('(')
        if(str[i] == '(')
        {
            // Parenthesis sequence length
            int length;
            
            length = getPrntsLength(str, i, len);
            
            char prntStr[length];
            clearString(prntStr, length);
            
            // Write sequence inside parenthesis into string (exclude parenthesis symbol)
            i++;
            for(int j = 0; j < length; j++, i++)
            {
                prntStr[j] = str[i];
            }
            i++;
            
            // Calculate string sequence in parenthesis
            n = Calculation(prntStr, length);
        }
        
        if(str[i] >= 48 && str[i] <= 57)
        {
            // Find how many digit in the number
            int digit;
            digit = findDigit(str, index);
            
            // Power Check
            if(str[index + digit + 1] == '^')
            {
                // string of Mult/Div sequence
                char nStr[len];
                clearString(nStr, len);
                
                int length;
                
                // Write sequence from main string
                for(int j = 0; i < len; j++, i++)
                {
                    // Check for parenthesis opening ('(')
                    if(str[i] == '(')
                    {
                        for(int k = i; k < len; k++, j++, i++)
                        {
                            nStr[j] = str[i];
                            if(str[i] == ')') break;
                        }
                    }
                    
                    // Stop when there is addition/subtraction
                    if( str[i] == '+' || str[i] == '-')
                    {
                        break;
                    }
                    // Stop when there is multiplication/division
                    if( str[i] == '*' || str[i] == '/')
                    {
                        break;
                    }
                    
                    nStr[j] = str[i]; // Write every char into string sequnce
                    length = j;
                }
                
                // Start Calculation
                n = PowCalculation(nStr, length);
            }
            // Multiplication & Division Check
            else if(str[index + digit + 1] == '*' || str[index + digit + 1] == '/')
            {
                // string of Mult/Div sequence
                char nStr[len];
                clearString(nStr, len);
                
                int length;
                
                // Write sequence from main string
                for(int j = 0; i < len; j++, i++)
                {
                    // Check for parenthesis opening ('(')
                    if(str[i] == '(')
                    {
                        for(int k = i; k < len; k++, j++, i++)
                        {
                            nStr[j] = str[i];
                            if(str[i] == ')') break;
                        }
                    }
                    
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
    
    // Sum every value in the sumArray
    int sum = 0;
    
    for(int i = 0; i < len; i++)
    {
        sum += sumArray[i];
    }
    
    return sum;
}

int start()
{
    char str[500];
    int len;
    
    printf("Enter Operation:\n");
    scanf("%[^\n]s", str);
    
    len = getLength(str);
    
    if( !Validate(str, len) ) return 0;
    
    printf("\nResult:\n");
    printf("%d", Calculation(str, len));
}

int main()
{
    start();
    
    return 0;
}

//2022 - Vincentius Gusti Putu Agung Bagus Mahendra
