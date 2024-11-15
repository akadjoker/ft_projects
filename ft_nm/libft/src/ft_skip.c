#include "libft.h"

void	ft_skip_char(const char *str, int *i, char c)
{
	if (str == NULL || i == NULL)
		return ;
	while (str[*i] == c)
		(*i)++;
}

void	ft_skip_chars(const char *str, int *i, char *base)
{
	if (str == NULL || i == NULL)
		return ;
	while (ft_chrindex(str[*i], base) != -1)
		(*i)++;
}

void	ft_skip_space(const char *str, int *i)
{
	if (str == NULL || i == NULL)
		return ;
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

void	ft_skip_spacenl(const char *str, int *i)
{
	if (str == NULL || i == NULL)
		return ;
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

