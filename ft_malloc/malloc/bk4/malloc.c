#include "malloc.h"
#include "libft.h"

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>

t_header header;

void init_zones()
{
    header.tinys  = 0;
    header.tiny = create_zone(header.tinys, TINY_ZONE_SIZE, 0);
    header.tinys++;
    header.total_memory = 0;
    header.total_zones  = 0;
}



void free_zones()
{
    t_zone *zone = header.tiny;
    while (zone != NULL)
    {
        t_zone *next = zone->next;
        destroy_zone(zone);
        unmap_memory(zone, sizeof(t_zone));
        zone = next;
    }
    header.tiny = NULL;
}

void print_zone(t_zone *zone)
{
    //printf("Zone %ld\n", zone->id);
    //printf("Capacity %ld\n", zone->capacity);
    printf("Used %ld\n", zone->used);
    printf("Type %d\n", zone->type);
    printf("Memory %ld\n", zone->memory);
}

void print_zones()
{
    word total = 0;
    t_zone *zone = header.tiny;
    while (zone != NULL)
    {
        print_zone(zone);
        total += zone->memory;
        zone = zone->next;
    }
    printf("Total %ld\n", total);
}


t_block* create_block(word size)
{
    t_block* block = map_memory(sizeof(t_block));
    block->size  = size;
    block->magic = MAGIC_NUMBER;
    block->zone  = 0;
    block->index = 0;
    block->free  = 0;
    return block;
}


void free_block(t_block *block)
{
    if (!block)
        return;
    unmap_memory(block, sizeof(t_block));
}

void free_block_zone(t_block *block)
{
    if (!block)
        return;

    t_zone *zone = header.tiny;
    while (zone != NULL)
    {
        if (zone->id == block->zone)
        {
            zone->memory -= block->size;
            zone->blocks[block->index]->free = 1;
            zone->used--;
            return;
        }
        zone = zone->next;
    }
}


t_zone* create_zone(word id,  word capacity, byte type)
{
    t_zone *zone = map_memory(sizeof(t_zone));
    zone->capacity = capacity;
    zone->memory = 0;
    zone->used = 0;
    zone->id = id;
    zone->type = type;
    zone->next = NULL;
    printf("Create Zone %ld\n", zone->id);
    zone->blocks = map_memory(capacity * sizeof(t_block*));
    for (word i = 0; i < capacity; i++)
    {
        zone->blocks[i] = create_block(0);
        zone->blocks[i]->zone  = id;
        zone->blocks[i]->index = i;
        zone->blocks[i]->free  = 1;
    }
    return zone;
}

void destroy_zone(t_zone *zone)
{
    for (word i = 0; i < zone->capacity; i++)
    {
        unmap_memory(zone->blocks[i], sizeof(t_block));
    }
    unmap_memory(zone->blocks, zone->capacity * sizeof(t_block*));
    unmap_memory(zone, sizeof(t_zone));
}

void *map_memory(word size)
{
    void *mem = mmap(NULL, size, 
                    PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (mem == MAP_FAILED)
        return NULL;
    
    return mem;

}

void unmap_memory(void *ptr, word size)
{
    munmap(ptr, size);
}




t_block* get_block(word size)
{
    if (size <= TINY_MAX)
    {

        t_zone *zone = header.tiny;
        while (zone)
        {
            for (word i = 0; i < zone->capacity; i++)
            {
                    t_block * block = zone->blocks[i];
                    if (block->free)
                    {
                        block->free = 0;
                        block->size = size;
                        zone->used++;
                        zone->memory += size;
                        return block;
                    }
            }
            zone = zone->next;
        }

        t_zone *new_zone = create_zone(header.tinys, TINY_ZONE_SIZE, 0);
        header.tinys++;
        new_zone->next = header.tiny;
        header.tiny = new_zone;
        return get_block(size);
    }
    printf("Out of memory\n");
    return NULL;
}


void* block_to_ptr(t_block *block)
{
    return (void*)((char*)block + sizeof(t_block));
}

t_block* ptr_to_block(void *ptr)
{
    return ((t_block*)(void*)((char*)ptr - sizeof(t_block)));
}

void *ft_malloc(word size)
{
    if (size == 0)
        return NULL;

    t_block *block = get_block(size);
    if (block)
    {
        return block_to_ptr(block);
    }
    return NULL;
}

void ft_free(void *ptr)
{
    if (!ptr)
        return;
    t_block *block = ptr_to_block(ptr);
    if (!block)
    {
        printf("Invalid block\n");
        return ;
    }
    if (block->magic != MAGIC_NUMBER)
    {
        printf("Invalid block\n");
        return ;
    }
    free_block_zone(block);
}
