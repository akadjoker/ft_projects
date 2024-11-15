
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


const int MAX=1024*28;

void test_calloc() 
{
    int *arr = (int *)calloc(MAX, sizeof(int));
    if (!arr) 
    {
        printf("FAIL: calloc returned NULL\n");
        return;
    }

    // Verifica se todos os elementos estão inicializados para 0
    for (int i = 0; i < MAX; i++) 
    {
        if (arr[i] != 0) 
        {
            printf("FAIL: calloc did not initialize to zero\n");
            free(arr);
            return;
        }
    }

    printf("PASS: calloc works\n");
    free(arr);
}





int main() 
{

for (int i=0;i<100;i++)
{
    char *string = strdup("Luis");

 //   printf("%s\n",string);

    free(string);

test_calloc();
}  

test_calloc();
   
   


    return 0;
}

