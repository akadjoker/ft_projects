
#include "internal.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_header g_header;

EXPORT void free(void *ptr)
{
    if (!ptr)
        return;

    pthread_mutex_lock(&g_malloc_mutex);

    t_block *block = (t_block *)((char *)ptr - META_SIZE);
    block->state = BLOCK_FREE;

    //cola a direita
    if (block->next && block->next->state == BLOCK_FREE)
    {
        block->size += block->next->size + META_SIZE;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }

    //    cola a esquerda
    if (block->prev && block->prev->state == BLOCK_FREE)
    {
        block->prev->size += block->size + META_SIZE;
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
