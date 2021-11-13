/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:24:53 by ovanessa          #+#    #+#             */
/*   Updated: 2020/11/22 13:43:57 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			new_c;
	char			*new_s;

	i = 0;
	new_c = (char)c;
	new_s = NULL;
	while (s[i])
	{
		if (s[i] == new_c)
			new_s = (char *)&s[i];
		i++;
	}
	if (new_c == s[i])
		return ((char *)&s[i]);
	return (new_s);
}
