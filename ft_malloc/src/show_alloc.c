
#include "ft_malloc.h"
#include "internal.h"

#include <stdio.h>

static inline size_t show_alloc(t_page *mem, const char *size_str)
{
	t_block *block;
	size_t total;

	total = 0;
	while (mem)
	{
		printf("%s : %p\n", size_str, mem);
		block = mem->alloc;
		while (block)
		{
			printf("%p - %p : %lu bytes\n", (void *)block + sizeof(t_block), (void *)block + sizeof(t_block) + block->size, block->size);
			total += block->size;
			block = block->next;
		}
		mem = mem->next;
	}
	return (total);
}

static inline size_t show_alloc_large(void)
{
	t_block *block;
	size_t total;

	total = 0;
	printf("LARGE : %p\n", g_malloc_pages.large);
	block = g_malloc_pages.large;
	while (block)
	{
		printf("%p - %p : %lu bytes\n", (void *)block + sizeof(t_block), (void *)block + sizeof(t_block) + block->size, block->size);
		total += block->size;
		block = block->next;
	}
	return (total);
}

EXPORT void show_alloc_mem(void)
{
	size_t total;

	total = 0;
	pthread_mutex_lock(&g_malloc_mutex);
	if (g_malloc_pages.tiny)
		total += show_alloc(g_malloc_pages.tiny, "TINY");
	if (g_malloc_pages.small)
		total += show_alloc(g_malloc_pages.small, "SMALL");
	if (g_malloc_pages.large)
		total += show_alloc_large();
	printf("Total : %lu bytes\n", total);
	pthread_mutex_unlock(&g_malloc_mutex);
}
