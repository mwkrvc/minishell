/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:40:28 by ovanessa          #+#    #+#             */
/*   Updated: 2021/04/24 22:41:40 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*new_b;

	new_b = (unsigned char *)b;
	while (len > 0)
	{
		new_b[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}
