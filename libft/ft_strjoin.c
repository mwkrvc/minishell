/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 20:38:09 by ovanessa          #+#    #+#             */
/*   Updated: 2021/06/14 14:19:06 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	unsigned int	total_len;
	char			*new_s;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	new_s = NULL;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2;
	new_s = malloc(sizeof(char) * (total_len + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, len1 + 1);
	ft_strlcat(new_s, s2, total_len + 1);
	return (new_s);
}
