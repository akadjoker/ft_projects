

#include "internal.h"
#include "libft.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_header g_header;



EXPORT void show_alloc_mem(void)
{
    if (!g_header.initialized)
    {
        ft_putstr("malloc not initialized\n");
        return;
    }
    pthread_mutex_lock(&g_malloc_mutex);

    size_t total = 0;
    t_zone *zone = g_header.g_zones;

    while (zone)
    {
        char *type_str;
        switch (zone->type)
        {
        case 0:
            type_str = "TINY";
            break;
        case 1:
            type_str = "SMALL";
            break;
        default:
            type_str = "LARGE";
            break;
        }

     //   printf("%s : %p\n", type_str, (void *)zone);

        ft_putstr(type_str);
        ft_putstr(" : ");
        ft_putaddr(zone);
        ft_putchar('\n');

        t_block *block = zone->blocks;
        while (block)
        {
            if (block->state == BLOCK_USED)
            {
                void *start = (char *)block + META_SIZE;
                void *end = (char *)start + block->size;
                ft_putaddr(start);
                ft_putstr(" - ");
                ft_putaddr(end);
                ft_putstr(" : ");
                ft_putnbr(block->size);
                ft_putstr(" bytes\n");

                //printf("%p - %p : %zu bytes\n", start, end, block->size);
                total += block->size;
            }
            block = block->next;
        }

        zone = zone->next;
    }

    ft_putstr("Total : ");
    ft_putnbr(total);
    ft_putstr(" bytes\n");

    //printf("Total : %zu bytes\n", total);
    pthread_mutex_unlock(&g_malloc_mutex);
}