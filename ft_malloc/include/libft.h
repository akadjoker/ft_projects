#ifndef LIBFT_H
#define LIBFT_H

# include <unistd.h>

void    *ft_memset(void *b, int c, size_t len);
void    *ft_memcpy(void *dst, const void *src, size_t n);
size_t  ft_strlen(const char *s);

void ft_putstr(char *s);
void ft_putchar(char c);
void ft_putnbr(int n);
void ft_putaddr(void *ptr);
void ft_printnrb(char *str, int n);

#endif
