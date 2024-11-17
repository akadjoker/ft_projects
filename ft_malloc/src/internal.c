
#include "ft_malloc.h"
#include "internal.h"
#include "libft.h"



/*
** Align memory on (mask + 1) bytes with (mask + 1) being a power of 2
*/

size_t		ft_align(size_t size, size_t mask)
{
	return ((size + mask) & ~mask);
}


size_t		page_size(size_t size)
{
	static const size_t	malloc_size[3] = {MALLOC_TINY, MALLOC_SMALL, 	MALLOC_LARGE};

	return (malloc_size[(size > ZONE_TINY) + (size > ZONE_SMALL)]);
}

bool	is_valid_block(const void *ptr, size_t size)
{
	void		*block_addr;
	t_block		*block;

	if (size > ZONE_SMALL)
		block = g_malloc_pages.large;
	else if (size > ZONE_TINY)
		block = (t_block*)g_malloc_pages.small + sizeof(t_page);
	else
		block = (t_block*)g_malloc_pages.tiny + sizeof(t_page);
	block_addr = block + sizeof(t_block);
	while (block && block_addr < ptr)
	{
		if (block_addr == ptr)
			return (true);
		block = block->next;
		block_addr = block + sizeof(t_block);
	}
	return (false);
}
