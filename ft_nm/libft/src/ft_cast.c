

#include "libft.h"

char	*ft_ultoa(unsigned long int n)
{
	unsigned long int	e;
	char				*str;
	int					i;

	i = 1;
	e = n / 10;
	while (e)
	{
		e /= 10;
		i++;
	}
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	while (i--)
		str[i] = ((n / ft_pow(10, e++)) % 10) + 48;
	return (str);
}



char	*ft_ultox(unsigned long int n)
{
	unsigned long int	e;
	short int			res;
	char				*str;
	int					i;

	i = 1;
	e = n / 16;
	while (e)
	{
		e /= 16;
		i++;
	}
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	while (i--)
	{
		res = ((n / ft_pow(16, e++)) % 16);
		if (res < 10)
			res += 48;
		else
			res += 87;
		str[i] = res;
	}
	return (str);
}


char	*ft_utox(unsigned int n)
{
	unsigned int	e;
	short int		res;
	char			*str;
	int				i;

	i = 1;
	e = n / 16;
	while (e)
	{
		e /= 16;
		i++;
	}
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	while (i--)
	{
		res = ((n / ft_pow(16, e++)) % 16);
		if (res < 10)
			res += 48;
		else
			res += 87;
		str[i] = res;
	}
	return (str);
}


char	*ft_utobx(unsigned int n)
{
	unsigned int	e;
	short int		res;
	char			*str;
	int				i;

	i = 1;
	e = n / 16;
	while (e)
	{
		e /= 16;
		i++;
	}
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	while (i--)
	{
		res = ((n / ft_pow(16, e++)) % 16);
		if (res < 10)
			res += 48;
		else
			res += 55;
		str[i] = res;
	}
	return (str);
}


char	*ft_utoa(unsigned int n)
{
	char			*str;
	unsigned int	e;
	int				i;

	i = 1;
	e = n / 10;
	while (e)
	{
		e /= 10;
		i++;
	}
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	while (i--)
		str[i] = ((n / ft_pow(10, e++)) % 10) + 48;
	return (str);
}


static int	count_cell(int n)
{
	int			i;
	int			e;

	if (n < 0)
		i = 2;
	else
		i = 1;
	e = n / 10;
	while (e != 0)
	{
		e /= 10;
		i++;
	}
	return (i);
}

static void	fill_itoa(int n, char *str, int i)
{
	short int	res;
	short int	stop;
	int			e;

	e = 0;
	stop = 0;
	if (n < 0)
		stop = 1;
	while (i-- > stop)
	{
		res = ((n / ft_pow(10, e++)) % 10);
		if (n > 0)
			str[i] = res + 48;
		else
			str[i] = res + 48 - (res * 2);
	}
	if (n < 0)
		str[i] = '-';
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;

	i = count_cell(n);
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	fill_itoa(n, str, i);
	return (str);
}


static int	count_cell_long(long n)
{
	int			i;
	long		e;

	if (n < 0)
		i = 2;
	else
		i = 1;
	e = n / 10;
	while (e != 0)
	{
		e /= 10;
		i++;
	}
	return (i);
}

static void	fill_ltoa(long n, char *str, int i)
{
	short int	res;
	short int	stop;
	int			e;

	e = 0;
	stop = 0;
	if (n < 0)
		stop = 1;
	while (i-- > stop)
	{
		res = ((n / ft_pow(10, e++)) % 10);
		if (n > 0)
			str[i] = res + 48;
		else
			str[i] = res + 48 - (res * 2);
	}
	if (n < 0)
		str[i] = '-';
}

char	*ft_ltoa(long n)
{
	char		*str;
	int			i;

	i = count_cell_long(n);
	str = ft_strnew(i);
	if (!(str))
		return (NULL);
	fill_ltoa(n, str, i);
	return (str);
}
