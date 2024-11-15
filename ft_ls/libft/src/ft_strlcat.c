/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:13:53 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:31 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i_max;
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (ft_strlen(src) + dstsize);
	i_max = dstsize - len_dst - 1;
	i = 0;
	while (i < i_max && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + ft_strlen(src));
}
