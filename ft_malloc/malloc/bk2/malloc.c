#include "malloc.h"
#include "libft.h"

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>

t_header header;

void init_zones()
{
    header.tinys  = 1;

    header.tiny  = map_memory(header.tinys * sizeof(t_zone));
    for (word i = 0; i < header.tinys; i++)
    {
       create_zone(i, &header.tiny[i], TINY_ZONE_SIZE, 0);
    }
    header.total_memory = 0;
    header.total_zones  = 0;
}

void expand_tiny_zone()
{
    word old_capacity = header.tinys;
    word new_capacity = header.tinys * 2;
    printf("Expand tiny zone from %ld to %ld\n", old_capacity, new_capacity);
    t_zone *new_zone = map_memory(new_capacity * sizeof(t_zone));
    for (word i = 0; i < old_capacity; i++)
    {
        ft_memcpy(&new_zone[i], &header.tiny[i], sizeof(t_zone));
    }
    for (word i = old_capacity; i < new_capacity; i++)
    {
        create_zone(i, &new_zone[i], TINY_ZONE_SIZE, 0);
    }
    unmap_memory(header.tiny, old_capacity * sizeof(t_zone));
    header.tinys = new_capacity;
    header.tiny  = new_zone;
}


void free_zones()
{
    for (word i = 0; i < header.tinys; i++)
    {
        destroy_zone(&header.tiny[i]);
    }
    unmap_memory(header.tiny,  header.tinys  * sizeof(t_zone));
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
    for (word i = 0; i < header.tinys; i++)
    {
        print_zone(&header.tiny[i]);
        total += header.tiny[i].memory;
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
    header.tiny[block->zone].memory -= block->size;
    header.tiny[block->zone].blocks[block->index]->free = 1;
    header.tiny[block->zone].used--;
}


void create_zone(word id, t_zone *zone, word capacity,byte type)
{
    zone->capacity = capacity;
    zone->used = 0;
    zone->id = id;
    zone->type = type;
    zone->blocks = map_memory(capacity * sizeof(t_block*));
    for (word i = 0; i < capacity; i++)
    {
        zone->blocks[i] = create_block(0);
        zone->blocks[i]->zone  = id;
        zone->blocks[i]->index = i;
        zone->blocks[i]->free  = 1;
    }
}

void destroy_zone(t_zone *zone)
{
    for (word i = 0; i < zone->capacity; i++)
    {
        unmap_memory(zone->blocks[i], sizeof(t_block));
    }
    unmap_memory(zone->blocks, zone->capacity * sizeof(t_block*));
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


        for (word i = 0; i < header.tinys; i++)
        {
            for (word j = 0; j < header.tiny[i].capacity; j++)
            {
                    t_block * block = header.tiny[i].blocks[j];
                    if (block->free)
                    {
                        block->free = 0;
                        block->size = size;
                        header.tiny[i].used++;
                        header.tiny[i].memory += size;
                        return block;
                    }
            }
        }
        expand_tiny_zone();
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
