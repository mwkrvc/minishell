/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:28:31 by ovanessa          #+#    #+#             */
/*   Updated: 2021/01/18 20:06:10 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	new_c;
	int		i;

	new_c = (char)c;
	i = 0;
	if (new_c == '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == new_c)
			return ((char *)&s[i]);
		i++;
	}
	if (new_c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
