/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:24:26 by ovanessa          #+#    #+#             */
/*   Updated: 2021/04/24 22:49:38 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	c_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	l;
	unsigned int	start;
	unsigned int	end;
	char			*new_s1;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (c_in_set(s1[i], set) && s1[i] != '\0')
		i++;
	start = i;
	l = ft_strlen(s1) - 1;
	if (start == l + 1)
		return (ft_substr("", 0, 1));
	while (c_in_set(s1[l], set) && s1[l])
		l--;
	end = l;
	new_s1 = ft_substr(s1, start, (end - start + 1));
	return (new_s1);
}
