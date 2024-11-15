
#include <signal.h>
#include "internal.h"
#include "ft_malloc.h"

pthread_mutex_t g_malloc_mutex;
t_header g_header = {0};


static void handle_usr1(int sig) 
{
    (void)sig;
    ft_putstr("[INFO] Sinal SIGUSR1\n");
    show_alloc_mem();
}

void handle_sigint(int signum) 
{
    (void)signum;
    ft_putstr("[INFO] Sinal SIGINT (Ctrl+C)\n");
    show_alloc_mem(); 
    exit(0);          
}

void mallock_init(void)
{
    g_header.TINY_ZONE_SIZE = getpagesize() * ((TINY_MAX_SIZE * 100 + sizeof(t_zone)) / getpagesize() + 1);
    g_header.SMALL_ZONE_SIZE = getpagesize() * ((SMALL_MAX_SIZE * 100 + sizeof(t_zone)) / getpagesize() + 1);
    g_header.initialized = 1;
    g_header.g_malloc_debug = 0;

    // printf("Malloc zones initialized (TINY: %zu, SMALL: %zu)\n",
    //       g_header.TINY_ZONE_SIZE, g_header.SMALL_ZONE_SIZE);
}


__attribute__((constructor))
static void mallocstart(void) 
{
    {
        //kill -USR1 <PID>
        struct sigaction sa;
        sa.sa_handler = handle_usr1;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGUSR1, &sa, NULL) == -1)
        {
            perror( "failed to set SIGUSR1 handler");
            return ;
        }
    }
    {
        struct sigaction sa;
        sa.sa_handler = handle_sigint;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGINT, &sa, NULL) == -1)
        {
        perror( "failed to set SIGINT handler");
        return ;
        }
    }
    mallock_init();
    char *debug_env = getenv("MALLOC_DEBUG");
    if (debug_env && debug_env[0] == '1')
    {
        ft_putstr("=== Malloc initialized ===\n");
        g_header.g_malloc_debug  = 1;
    }
}

__attribute__((destructor))
static void mallocend(void) 
{
   
    if ( g_header.g_malloc_debug)
    {
        ft_putstr("=== Malloc destroyed ===\n");
        show_alloc_mem();
    }
}



// Verificar se o ponteiro esta dentro das  zonas
int is_valid_pointer(void *ptr)
{
    t_zone *zone = g_header.g_zones;
    while (zone)
    {
        if (ptr >= (void *)zone && ptr < (void *)((char *)zone + zone->size))
            return 1;
        zone = zone->next;
    }
    return 0;
}


 size_t align_size(size_t size)
{
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

 t_zone *create_zone(size_t total_size, int type)
{
    void *addr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;

    t_zone *zone = (t_zone *)addr;
    zone->size = total_size;
    zone->type = type;
    zone->next = NULL;

   
    t_block *block = (t_block *)((char *)addr + sizeof(t_zone));
    block->size = total_size - sizeof(t_zone) - META_SIZE;
    block->state = BLOCK_FREE;
    block->next = NULL;
    block->prev = NULL;
    zone->blocks = block;

    return zone;
}

 t_block *find_free_block(t_zone *zone, size_t size)
{
    t_block *block = zone->blocks;
    while (block)
    {
        if (block->state == BLOCK_FREE && block->size >= size)
            return block;
        block = block->next;
    }
    return NULL;
}

 void split_block(t_block *block, size_t size)
{
    size_t remaining = block->size - size - META_SIZE;
    if (remaining >= META_SIZE + ALIGNMENT)
    {
        t_block *new_block = (t_block *)((char *)block + META_SIZE + size);
        new_block->size = remaining - META_SIZE;
        new_block->state = BLOCK_FREE;
        new_block->next = block->next;
        new_block->prev = block;
        if (block->next)
            block->next->prev = new_block;
        block->next = new_block;
        block->size = size;
    }
}

