#include "../../includes/minishell.h"

void	ft_arrayfree(char **array)
{
	int	i;

	i = -1;
	while (array && array[++i])
	{
		free(array[i]);
	}
	free(array);
}

int	ft_arraylen(char *array[])
{
	int	i;

	if (array == NULL)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_arraypush(char *array[], const char *s)
{
	char	**copy;
	int		len;
	int		i;

	if (!s)
		return (array);
	if (array)
		len = ft_arraylen(array) + 1;
	else
		len = 1;
	copy = (char **)malloc(sizeof(*array) * (len + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (array && array[++i])
		copy[i] = ft_strdup(array[i]);
	copy[len - 1] = ft_strdup(s);
	copy[len] = NULL;
	ft_arrayfree(array);
	return (copy);
}
