#ifndef LIBMALLOC_H
#define LIBMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para getpagesize()

#define ALIGNMENT 16 // Alinhamento padrão


#define ZONE_TINY  0
#define ZONE_SMALL 1


#define TINY_MAX 16   // n bytes
#define SMALL_MAX 128 // m bytes
#define MIN_ALLOC_PER_ZONE 100 // subject say so ,  ;) 
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define MAGIC_NUMBER 0x42

// Calculate zone sizes based on page size and minimum allocations
#define PAGE_SIZE ((size_t)getpagesize())

#define TINY_ZONE_SIZE  (PAGE_SIZE * ((TINY_MAX * MIN_ALLOC_PER_ZONE + PAGE_SIZE - 1) / PAGE_SIZE))
#define SMALL_ZONE_SIZE (PAGE_SIZE * ((SMALL_MAX * MIN_ALLOC_PER_ZONE + PAGE_SIZE - 1) / PAGE_SIZE))
#define LARGE_ZONE_SIZE (32)


typedef unsigned char byte;
typedef size_t   word;


typedef struct s_block
{
    byte free;    // 1 se livre, 0 se ocupado
    byte magic;   // se foi criado pelo malloc
    word zone ;   // Zona onde o bloco pertence
    word size;  // Tamanho do bloco
    word index; // Índice do bloco
    char padding[ALIGNMENT - ((sizeof(byte) + sizeof(byte)+ sizeof(word) + sizeof(word) + sizeof(word)) % ALIGNMENT)];
    void *data; // Ponteiro para os dados , nosso bloco
} t_block;

typedef struct s_zone
{
    t_block **blocks; // array para os blocos
    byte type ;    // 0 = tiny, 1 = small , 2 = large
    word capacity; // Capacidade máxima (em número de blocos)
    word used;     // Blocos usados
    word id ;      // ID da zona
} t_zone;



typedef struct s_header
{
    t_zone  *tiny;
    t_zone  *small;
    t_zone  *large;
    word tinys;
    word smalls;
    word larges;
    word total_memory;
    word total_zones;
} t_header;

void init_zones();
void free_zones();

void create_zone(word id, t_zone *zone, word capacity,byte type,byte fill);
void destroy_zone(t_zone *zone);

void *map_memory(word size);
void unmap_memory(void *ptr, word size);

void *ft_malloc(word size);
void ft_free(void *ptr);

#endif
