#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stddef.h>




 void *malloc(size_t size);
 void free(void *ptr);
 void *realloc(void *ptr, size_t size);
 void *calloc(size_t nmemb, size_t size);


 void show_alloc_mem(void);

#define ft_malloc malloc
#define ft_free free
#define ft_realloc realloc

#endif