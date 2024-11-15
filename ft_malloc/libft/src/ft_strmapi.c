/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:16:44 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:31 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*strmap;

	if (!s || !f)
		return (NULL);
	strmap = (char *)malloc(sizeof(*strmap) * (ft_strlen(s) + 1));
	if (!(strmap))
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		strmap[i] = (*f)(i, s[i]);
	strmap[i] = '\0';
	return (strmap);
}
