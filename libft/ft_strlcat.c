/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:12:53 by ovanessa          #+#    #+#             */
/*   Updated: 2020/11/28 17:09:10 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	size_dst;
	int				size_src;

	i = 0;
	size_dst = 0;
	size_src = 0;
	while (src[size_src] != '\0')
		size_src++;
	if (dstsize == 0)
		return (size_src);
	while (size_dst < dstsize && dst[size_dst])
		size_dst++;
	if (dstsize <= size_dst)
		return (dstsize + size_src);
	i = 0;
	while (dstsize && (--dstsize - size_dst) && src[i])
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	dst[size_dst + i] = '\0';
	return (size_src + size_dst);
}
