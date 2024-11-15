

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	else
		return (c);
}

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	else
		return (c);
}

int	ft_chrcount(int c, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_chrindex(int c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int	ft_isalpha(int c)
{
	return ((c > 64 && c < 91) || (c > 96 && c < 123));
}


int ft_islower(int c) { return (c >= 'a' && c <= 'z'); }

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
