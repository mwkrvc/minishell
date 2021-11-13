/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:34:41 by ovanessa          #+#    #+#             */
/*   Updated: 2020/11/23 20:40:49 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;
	unsigned char	new_c;
	size_t			i;

	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	new_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		if (new_src[i] == new_c)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}
