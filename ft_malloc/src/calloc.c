
#include "ft_malloc.h"
#include "internal.h"

EXPORT void	*calloc(size_t count, size_t size)
{
	void			*ptr;
	if ((ptr = malloc(count * size)))
    {
		ft_memset(ptr, 0, count * size);
    }
	return (ptr);
}
