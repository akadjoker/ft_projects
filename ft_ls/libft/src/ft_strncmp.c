/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:13:10 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/14 08:10:38 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_cp;
	const unsigned char	*s2_cp;

	s1_cp = (const unsigned char *)s1;
	s2_cp = (const unsigned char *)s2;
	while (n--)
	{
		if (!*s1_cp || !*s2_cp)
			return (*s1_cp - *s2_cp);
		if (*s1_cp++ != *s2_cp++)
			return (*--s1_cp - *--s2_cp);
	}
	return (0);
}
