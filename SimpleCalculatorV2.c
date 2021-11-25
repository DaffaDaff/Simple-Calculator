#include <stdio.h>
#include <string.h>
#include <math.h>

char str[500];
int lenght;

int start()
{
    printf("Enter Operation: \n");
    scanf("%[^\n]s", str);
    
    lenght = strlen(str);
    printf("%d", lenght);
}

int main()
{
    start();
    
    return 0;
}
