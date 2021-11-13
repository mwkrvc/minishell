/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovanessa <ovanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:15:40 by ovanessa          #+#    #+#             */
/*   Updated: 2021/04/24 22:48:44 by ovanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		w_count;
	int		i;

	i = 0;
	w_count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c)
			w_count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (w_count);
}

static char	*size_words(char const *s, char c)
{
	char	*arr;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**free_lloc(char **res, int arr)
{
	int		i;

	i = 0;
	while (i < arr)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_res(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		arr;
	int		i;

	i = 0;
	arr = 0;
	res = ft_res(s, c);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			res[arr] = size_words(&s[i], c);
			if (!res[arr])
				return (free_lloc(res, arr));
			arr++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	res[arr] = NULL;
	return (res);
}
