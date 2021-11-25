#include <stdio.h>


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

int main()
{
    char str[500];
    int len;
    
    scanf("%s", str);
    
    len = getLength(str);
    
    
    
    return 0;
}

