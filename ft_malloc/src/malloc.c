
#include "ft_malloc.h"
#include "internal.h"
#include "libft.h"
t_malloc_pages g_malloc_pages = {0, 0, 0};
pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static inline void *block_create(t_block **free, t_block **alloc, const size_t size)
{
	t_block *block;

	block = *free;
	if ((*free = block->next))
		(*free)->prev = NULL;
	if ((block->next = *alloc))
		(*alloc)->prev = block;
	(*alloc) = block;
	block->size = size;
	return (block + 1);
}


static inline void mem_init_zone(t_page **page, t_page *mem, const size_t zone_size)
{
	t_block *free_block;

	free_block = (void *)mem + sizeof(t_page);
	mem->prev = NULL;
	if ((mem->next = *page))
		mem->next->prev = mem;
	*page = mem;
	mem->alloc = NULL;
	mem->free = free_block;
	while ((void *)free_block + (zone_size + sizeof(t_block)) * 2 < (void *)mem + zone_size * MALLOC_ZONE)
	{
		free_block->next = (void *)free_block + sizeof(t_block) + zone_size;
		free_block->next->prev = free_block;
		free_block = free_block->next;
	}
	free_block->next = NULL;
}

static inline void *malloc_tiny_small(t_page **page, const size_t zone_size, const size_t size)
{
	t_page *mem;

	mem = *page;
	while (mem && !mem->free)
		mem = mem->next;
	if (!mem)
	{
		if ((mem = mmap(0, zone_size * MALLOC_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		{
			ft_putstr("Fail to map  memory\n");
			return NULL;
		}
		mem_init_zone(page, mem, zone_size);
	}
	return (block_create(&mem->free, &mem->alloc, ft_align(size, 31)));
}


static void *malloc_large(size_t size)
{
	const size_t msize = ft_align(size + sizeof(t_block), getpagesize() - 1);
	t_block *block;

	if (((block = mmap(0, msize * 100, PROT_READ | PROT_WRITE,MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED))
		{
			ft_putstr("Fail to map  large memory\n");
			return NULL;
		}
	block->size = ft_align(size, 31);
	block->prev = NULL;
	if ((block->next = g_malloc_pages.large))
		g_malloc_pages.large->prev = block;
	g_malloc_pages.large = block;
	return ((void *)block + sizeof(t_block));
}


EXPORT void *malloc(size_t size)
{
	const size_t type = (size > ZONE_TINY) + (size > ZONE_SMALL);
	void *ptr;

	if (!size)
		return (NULL);
	pthread_mutex_lock(&g_malloc_mutex);
	if (type == MALLOC_TINY)
		ptr = malloc_tiny_small(&g_malloc_pages.tiny, ZONE_TINY, size);
	else if (type == MALLOC_SMALL)
		ptr = malloc_tiny_small(&g_malloc_pages.small, ZONE_SMALL, size);
	else
		ptr = malloc_large(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
