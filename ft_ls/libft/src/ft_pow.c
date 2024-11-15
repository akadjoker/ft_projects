
#include "libft.h"

long	ft_pow(int base, int power)
{
	long	result;

	result = 1;
	while (power--)
		result *= base;
	return (result);
}
