

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	char	*adr;
	int		i;

	while (*s1 && (ft_strchr(set, *s1)))
		s1++;
	adr = (char *)s1;
	while (*s1)
		s1++;
	if (adr != s1)
		while ((ft_strchr(set, *(s1 - 1))) && (s1 - 1) != adr)
			s1--;
	trimed = ft_strnew(s1 - adr);
	if (!(trimed))
		return (NULL);
	i = 0;
	while (adr != s1)
		*(trimed + i++) = *adr++;
	return (trimed);
}
