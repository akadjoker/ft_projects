#include "libft.h"

char	*ft_strnew(int size)
{
	char	*new;

	new = (char *)malloc(sizeof(*new) * (size += 1));
	if (!(new))
		return (NULL);
	while (size--)
		new[size] = 0;
	return (new);
}
