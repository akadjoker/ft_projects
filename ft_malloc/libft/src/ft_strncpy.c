/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:13:30 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:02 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*dst_cpy;
	size_t	i;

	i = 0;
	dst_cpy = dst;
	while (*src && i++ < len)
		*dst++ = *src++;
	while (i++ < len)
		*dst++ = 0;
	return (dst_cpy);
}
