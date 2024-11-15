
#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	nbr;
	int				i;
	int				neg;

	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	neg = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg = 1;
	nbr = 0;
	while (ft_isdigit(str[i]))
		nbr = nbr * 10 + str[i++] - 48;
	if (neg)
		return ((int)(-nbr));
	else
		return ((int) nbr);
}
