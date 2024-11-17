#include "malloc.h"
#include "libft.h"

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>

// Global state
static t_header header = {0};
static pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void print_zone(t_zone *zone)
{
    // printf("Zone %ld\n", zone->id);
    // printf("Capacity %ld\n", zone->capacity);
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

void free_block(t_block *block)
{
    if (!block)
        return;
    unmap_memory(block, sizeof(t_block));
}

void free_block_zone(t_block *block)
{
    if (!block)
    {
        printf("Invalid block\n");
        return;
    }
    t_zone *zone = header.tiny;
    while (zone)
    {
        if (zone->id == block->zone)
        {
            block->free = 1;
            zone->memory -= block->size;
            block->size = 0;
            zone->used--;
            return;
        }
        zone = zone->next;
    }
    printf("Invalid zone\n");
}

void destroy_zone(t_zone *zone)
{
    if (!zone)
        return;
    if (zone->blocks)
        unmap_memory(zone->blocks, zone->capacity * sizeof(t_block *));
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
// Initialize the memory zones
void init_zones(void)
{
    pthread_mutex_lock(&malloc_mutex);
    if (!header.tiny)
    {
        header.tinys = 0;
        header.tiny = create_zone(header.tinys, TINY_ZONE_SIZE, 0);
        if (header.tiny)
        {
            header.tinys++;
            header.total_memory = 0;
            header.total_zones = 1;
        }
    }
    pthread_mutex_unlock(&malloc_mutex);
}

// Safely clean up all zones
void free_zones(void)
{
    pthread_mutex_lock(&malloc_mutex);
    t_zone *current = header.tiny;
    while (current)
    {
        t_zone *next = current->next;
        if (current->blocks)
        {
            unmap_memory(current->blocks, current->capacity * sizeof(t_block));
        }
        unmap_memory(current, sizeof(t_zone));
        current = next;
    }
    header.tiny = NULL;
    header.tinys = 0;
    header.total_memory = 0;
    header.total_zones = 0;
    pthread_mutex_unlock(&malloc_mutex);
}

// Create a new memory block
t_block *create_block(word size, word zone_id, word index)
{
    t_block *block = map_memory(sizeof(t_block));
    if (!block)
        return NULL;

    block->size = size;
    block->magic = MAGIC_NUMBER;
    block->zone = zone_id;
    block->index = index;
    block->free = 0;
    return block;
}

// Create a new zone
t_zone *create_zone(word id, word capacity, byte type)
{
    t_zone *zone = map_memory(sizeof(t_zone));
    if (!zone)
        return NULL;

    zone->blocks = map_memory(capacity * sizeof(t_block));
    if (!zone->blocks)
    {
        unmap_memory(zone, sizeof(t_zone));
        return NULL;
    }

    zone->capacity = capacity;
    zone->memory = 0;
    zone->used = 0;
    zone->id = id;
    zone->type = type;
    zone->next = NULL;

    // Initialize all blocks in the zone
    for (word i = 0; i < capacity; i++)
    {
        t_block *block = (t_block *)((char *)zone->blocks + i * sizeof(t_block));
        block->size = 0;
        block->magic = MAGIC_NUMBER;
        block->zone = id;
        block->index = i;
        block->free = 1;
    }

    return zone;
}

// Find an available block or create a new zone if needed
static t_block *get_block(word size)
{
    if (size > TINY_MAX)
        return NULL;

    pthread_mutex_lock(&malloc_mutex);
    t_zone *zone = header.tiny;
    t_block *result = NULL;

    while (zone && !result)
    {
        for (word i = 0; i < zone->capacity; i++)
        {
            t_block *block = (t_block *)((char *)zone->blocks + i * sizeof(t_block));
            if (block->free)
            {
                block->magic = MAGIC_NUMBER;
                block->size = size;
                block->free = 0;
                block->index = i;
                zone->used++;
                zone->memory += size;
                result = block;
                break;
            }
        }
        zone = zone->next;
    }

    if (!result)
    {
        // Create new zone if no space found
        t_zone *new_zone = create_zone(header.tinys++, TINY_ZONE_SIZE, 0);
        if (new_zone)
        {
            new_zone->next = header.tiny;
            header.tiny = new_zone;
            header.total_zones++;
            result = get_block(size); // Recursive call to allocate in new zone
        }
    }

    pthread_mutex_unlock(&malloc_mutex);
    return result;
}

// Convert between block and user pointer
static inline void *block_to_ptr(t_block *block)
{
    return block ? (void *)((char *)block + sizeof(t_block)) : NULL;
}

static inline t_block *ptr_to_block(void *ptr)
{
    return ptr ? (t_block *)((char *)ptr - sizeof(t_block)) : NULL;
}

// Main malloc implementation
void *ft_malloc(word size)
{
    if (size == 0)
        return NULL;

    // Initialize zones if needed
    if (!header.tiny)
        init_zones();

    t_block *block = get_block(size);
    return block_to_ptr(block);
}

// Main free implementation
void ft_free(void *ptr)
{
    if (!ptr)
        return;

    pthread_mutex_lock(&malloc_mutex);

    t_block *block = ptr_to_block(ptr);
    if (!block || block->magic != MAGIC_NUMBER)
    {
        printf("Invalid block\n");
        pthread_mutex_unlock(&malloc_mutex);
        return;
    }

    t_zone *zone = header.tiny;
    while (zone)
    {
        if (zone->id == block->zone)
        {
            block->free = 1;

            zone->memory -= block->size;
            block->size = 0;
            zone->used--;
            break;
        }
        zone = zone->next;
    }

    pthread_mutex_unlock(&malloc_mutex);
}