#include "libft.h"


void    *ft_memset(void *b, int c, size_t len)
{
    unsigned char   *ptr;
    
    ptr = (unsigned char*)b;
    while (len--)
        *ptr++ = (unsigned char)c;
    return (b);
}


void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;

    if (!dst && !src)
        return (NULL);
    d = (unsigned char*)dst;
    s = (const unsigned char*)src;
    while (n--)
        *d++ = *s++;
    return (dst);
}



size_t  ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}



void ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return;
	}
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr((n / 10));		
        ft_putnbr((n % 10));
	}
	else
		ft_putchar((n + '0'));
}



void ft_putnbr_base(size_t nbr, char *base, int base_len)
{
	if (nbr >= (size_t)base_len)
	{
		ft_putnbr_base(nbr / base_len, base, base_len);
		ft_putnbr_base(nbr % base_len, base, base_len);
	}
	else
	{
		ft_putchar(base[nbr]);
	}
}

void ft_putaddr(void *ptr)
{
	ft_putstr("0x");
	ft_putnbr_base((size_t)ptr, "0123456789ABCDEF", 16);
}

void ft_printnrb(char* str,int n)
{
	ft_putstr(str);
	ft_putnbr(n);
	ft_putstr("\n");
}
