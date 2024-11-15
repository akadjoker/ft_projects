#include "internal.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_header g_header;


EXPORT void *calloc(size_t nmemb, size_t size)
{
  
    size_t total_size = nmemb * size;
    void *ptr = malloc(total_size);
    if (ptr) 
    {
        ft_bzero(ptr,total_size);
    }
    return ptr;
}