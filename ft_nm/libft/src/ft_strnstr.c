/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:14:06 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:31 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0 || needle == haystack)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] && len - i >= needle_len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char*)haystack + i);
		i++;
	}
	return (NULL);
}
