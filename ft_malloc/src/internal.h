#ifndef INTERNAL_H
#define INTERNAL_H
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include <sys/mman.h>
# include <pthread.h>


#define EXPORT __attribute__((visibility("default")))

extern pthread_mutex_t	g_malloc_mutex;


# define ZONE_SMALL		(1 << 10)
# define ZONE_TINY		(1 << 6)
# define MALLOC_ZONE	(1 << 7)
# define MASK_0XFFF		(1 << 12) - 1

typedef	enum
{
	MALLOC_TINY,
	MALLOC_SMALL,
	MALLOC_LARGE
}	t_malloc_type;



typedef struct			s_block
{
	struct s_block		*next;
	struct s_block		*prev;
	size_t				size;
	size_t				for_align_purpose;
} t_block;

typedef struct			s_page
{
	struct s_page		*next;
	struct s_page		*prev;
	t_block				*alloc;
	t_block				*free;
}						t_page;


typedef struct			s_malloc_pages
{
	t_page				*tiny;
	t_page				*small;
	t_block				*large;
}						t_malloc_pages;
extern t_malloc_pages	g_malloc_pages;


size_t					ft_align(size_t size, size_t mask);
bool					is_valid_block(const void *ptr, size_t size);
bool					malloc_error(const int err, const char *str);
size_t					page_size(size_t type);


#endif
