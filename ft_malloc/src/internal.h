#ifndef FT_MALLOC_INTERNAL_H
#define FT_MALLOC_INTERNAL_H

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>
#include <fcntl.h>
#include "libft.h"


#define EXPORT __attribute__((visibility("default")))

// Debug mode
#ifdef DEBUG
#define DEBUG_FD open("/tmp/malloc.log", O_WRONLY | O_CREAT | O_APPEND, 0644)
#endif

// Tamanhos e limites
#define TINY_MAX_SIZE 128
#define SMALL_MAX_SIZE 1024
#define ALIGNMENT 16
#define META_SIZE (sizeof(t_block))

// Estados dos blocos
#define BLOCK_FREE 0
#define BLOCK_USED 1

// Tipos de zona
#define ZONE_TINY 0
#define ZONE_SMALL 1
#define ZONE_LARGE 2

// Estrutura para um bloco de memória
typedef struct s_block
{
    size_t size;          // Tamanho do bloco (sem metadata)
    int state;            // BLOCK_FREE ou BLOCK_USED
    struct s_block *next; // Próximo bloco na zona
    struct s_block *prev; // Bloco anterior na zona
} t_block;

// Estrutura para uma zona de memória
typedef struct s_zone
{
    size_t size;         // Tamanho total da zona
    int type;            // TINY, SMALL ou LARGE
    struct s_zone *next; // Proxima zona
    t_block *blocks;     // Primeiro bloco na zona
} t_zone;

typedef struct s_malloc_stats
{
    size_t total_allocated;
    size_t total_freed;
    size_t number_of_allocs;
    size_t number_of_frees;
    size_t largest_alloc;
    size_t smallest_alloc;
} t_malloc_stats;

typedef struct s_header
{
    t_zone *g_zones;
    t_malloc_stats g_malloc_stats;
    size_t TINY_ZONE_SIZE;
    size_t SMALL_ZONE_SIZE;
    int initialized;
    int g_malloc_debug;
} t_header;

# define RED    "\x1B[31m"
# define GREEN  "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE   "\x1B[34m"
# define RESET  "\x1B[0m"



void mallock_init(void);
t_zone *create_zone(size_t total_size, int type);
t_block *find_free_block(t_zone *zone, size_t size);
void split_block(t_block *block, size_t size);
int is_valid_pointer(void *ptr);
size_t align_size(size_t size);


#endif