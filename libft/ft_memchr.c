/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:50:14 by ovanessa          #+#    #+#             */
/*   Updated: 2020/11/22 13:42:36 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*new_s;
	unsigned char	new_c;
	size_t			i;

	new_s = (unsigned char *)s;
	new_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (new_s[i] == new_c)
			return ((void *)&new_s[i]);
		i++;
	}
	return (NULL);
}
