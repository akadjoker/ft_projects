/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:15:19 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:31 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		bufsize;

	if (!s1 || !s2)
		return (NULL);
	bufsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(sizeof(*s3) * bufsize);
	if (!(s3))
		return (NULL);
	ft_strlcpy(s3, s1, bufsize);
	ft_strlcat(s3, s2, bufsize);
	return (s3);
}
