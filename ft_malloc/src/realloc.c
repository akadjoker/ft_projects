
#include "ft_malloc.h"
#include "internal.h"
#include "libft.h"





EXPORT void	*realloc(void *ptr, size_t size)
{
	void		*new;
	t_block		*block_header;

	if (!ptr || !size)
		return (malloc(size));
	pthread_mutex_lock(&g_malloc_mutex);
	if (!is_valid_block(ptr, size))
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (NULL);
	}
	block_header = ptr - sizeof(t_block);
	if (size <= block_header->size)
	{
		block_header->size = size;
		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	if (!(new = malloc(size)))
		return (NULL);
	ft_memcpy(new, ptr, block_header->size);
	free(ptr);
	return (new);
}


