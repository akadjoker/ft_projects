
#include <stdio.h>
#include "ft_malloc.h"



int main() 
{
    printf("=== Teste de malloc ===\n");
    char *ptr1 = malloc(64);
    char *ptr2 = malloc(128);
    char *ptr3 = malloc(2000);

    if (ptr1 && ptr2 && ptr3) 
    {
        printf("Alocações realizadas com sucesso.\n");
    } else 
    {
        printf("Erro ao alocar memória.\n");
    }

    printf("\n=== Teste de show_alloc_mem ===\n");
    show_alloc_mem();

    printf("\n=== Teste de realloc ===\n");
    ptr2 = realloc(ptr2, 256);
    if (ptr2) 
    {
        printf("Realloc realizado com sucesso.\n");
    } else 
    {
        printf("Erro ao realizar realloc.\n");
    }

    printf("\n=== Teste de free ===\n");
    free(ptr1);
    free(ptr2);
    free(ptr3);

    printf("\n=== Estado final de show_alloc_mem ===\n");
    show_alloc_mem();

    return 0;
}

