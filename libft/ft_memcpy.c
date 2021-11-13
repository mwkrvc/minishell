/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:22:33 by ovanessa          #+#    #+#             */
/*   Updated: 2021/07/24 19:50:21 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*new_src;
	unsigned char	*new_dst;
	size_t			i;

	i = 0;
	new_src = (unsigned char *)src;
	new_dst = (unsigned char *)dst;
	while (i < n)
	{
		*new_dst++ = *new_src++;
		i++;
	}
	return (dst);
}
