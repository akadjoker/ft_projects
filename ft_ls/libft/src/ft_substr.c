

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	sub = ft_strnew(len);
	if (!(sub))
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
		while (i < len && s[start])
			sub[i++] = s[start++];
	return (sub);
}
