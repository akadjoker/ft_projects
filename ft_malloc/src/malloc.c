
#include "internal.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_header g_header;

EXPORT void *malloc(size_t size)
{
    if (!g_header.initialized)
    {
        mallock_init();
    }
    pthread_mutex_lock(&g_malloc_mutex);

    if (size == 0)
    {
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL;
    }

    // Align 
    size = align_size(size);


    int zone_type;
    size_t zone_size;
    if (size <= TINY_MAX_SIZE)
    {
        zone_type = ZONE_TINY; 
        zone_size = g_header.TINY_ZONE_SIZE;
    }
    else if (size <= SMALL_MAX_SIZE)
    {
        zone_type = ZONE_SMALL; 
        zone_size = g_header.SMALL_ZONE_SIZE;
    }
    else
    {
        zone_type = ZONE_LARGE; 
        zone_size = size + sizeof(t_zone) + META_SIZE;
        zone_size = align_size(zone_size);
    }


    t_zone *zone = g_header.g_zones;
    t_zone *prev_zone = NULL;
    while (zone)
    {
        if (zone->type == zone_type)
        {
            t_block *block = find_free_block(zone, size);
            if (block)
            {
                block->state = BLOCK_USED;
                split_block(block, size);
                pthread_mutex_unlock(&g_malloc_mutex);
                return (char *)block + META_SIZE;
            }
        }
        prev_zone = zone;
        zone = zone->next;
    }

    zone = create_zone(zone_size, zone_type);
    if (!zone)
    {
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL;
    }


    if (prev_zone)
        prev_zone->next = zone;
    else
        g_header.g_zones = zone;


    t_block *block = zone->blocks;
    block->state = BLOCK_USED;
    split_block(block, size);

    pthread_mutex_unlock(&g_malloc_mutex);
    return (char *)block + META_SIZE;
}
