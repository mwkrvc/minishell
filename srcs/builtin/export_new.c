#include "../../includes/minishell.h"

char	*malloc_name(char *env)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	while (env[len] != '=')
		len++;
	result = (char *)malloc(sizeof (char) * (len + 1));
	while (env[i] != '=')
	{
		result[i] = env[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*malloc_value(char *env)
{
	int		iter_save[2];
	int		len;
	char	*result;

	iter_save[0] = 0;
	while (env[iter_save[0]] != '=')
		iter_save[0]++;
	iter_save[0]++;
	iter_save[1] = iter_save[0];
	len = 0;
	while (env[iter_save[0]])
	{
		iter_save[0]++;
		len++;
	}
	result = (char *) malloc(sizeof(char) * (len + 1));
	iter_save[0] = 0;
	while (env[iter_save[1]])
	{
		result[iter_save[0]] = env[iter_save[1]];
		iter_save[0]++;
		iter_save[1]++;
	}
	result[iter_save[0]] = '\0';
	return (result);
}

char	**split_export(char *env)
{
	char	**result;

	if (!ft_strchr(env, '='))
	{
		result = (char **) malloc(sizeof (char *) * 2);
		result[0] = ft_strdup(env);
		result[1] = NULL;
		return (result);
	}
	result = (char **) malloc(sizeof (char *) * 3);
	result[0] = malloc_name(env);
	result[1] = malloc_value(env);
	result[2] = NULL;
	return (result);
}
