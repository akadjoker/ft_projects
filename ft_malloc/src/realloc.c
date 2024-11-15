

#include "internal.h"
#include "libft.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_header g_header;

EXPORT void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(size);

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    t_block *block = (t_block *)((char *)ptr - META_SIZE);
    if (block->size >= size)
    {

        split_block(block, size);
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    pthread_mutex_unlock(&g_malloc_mutex);


    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}