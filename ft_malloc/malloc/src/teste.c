
#include "libft.h"
#include "malloc.h"
#include <string.h>

char* StrDup(char* str) 
{
    word size = ft_strlen(str) + 1;
    char* new = ft_malloc(size);
    ft_memcpy(new, str, size);
    new[size - 1] = '\0';
    return new;
}

int main() 
{

    init_zones();

        
for (word i = 0; i < 10; i++)
{
    char* str = StrDup("Luis Miguel Rosa dos Santos\n");
    ft_putstr(str);
    ft_free(str);
}


    #define STRESS_TEST_COUNT 5000
    void *pointers[STRESS_TEST_COUNT];

    for (int i = 0; i < STRESS_TEST_COUNT; i++)
    {
        size_t size = 32;
        pointers[i] = ft_malloc(size);
        if (!pointers[i])
        {
            printf("Stress test: Failed to allocate at iteration %d\n", i);
            break;
        }
        memset(pointers[i], i % 256, size);
    }
   print_zones();

    for (int i = 0; i < STRESS_TEST_COUNT; i++)
    {
        if (pointers[i])
        {

           ft_free(pointers[i]);
        }
    }


   
    print_zones();


    free_zones();



    return 0;
}

