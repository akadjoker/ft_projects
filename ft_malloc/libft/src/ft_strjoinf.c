
#include "libft.h"

char *ft_strjoinf (char *s1, int f1, char *s2, int f2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (new);
}
