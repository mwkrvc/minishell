/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:14:28 by ovanessa          #+#    #+#             */
/*   Updated: 2021/07/24 19:49:01 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*space;
	unsigned int	i;
	unsigned int	total_size;

	i = 0;
	total_size = count * size;
	space = (char *)malloc(total_size);
	if (!space)
		return (NULL);
	while (total_size)
	{
		space[i] = 0;
		i++;
		total_size--;
	}
	return ((void *)space);
}
