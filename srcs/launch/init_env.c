#include "../../includes/minishell.h"

int	add_env(char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	save = g_env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (g_env == NULL)
	{
		g_env = new;
		return (0);
	}
	while (g_env->next != NULL)
		g_env = g_env->next;
	g_env->next = new;
	g_env = save;
	return (0);
}

int	init_env(char **envp)
{
	char	**tmp;
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		name = ft_strdup(tmp[0]);
		value = ft_strdup(tmp[1]);
		add_env(name, value);
		free_arr(tmp);
		free(name);
		free(value);
		i++;
	}
	return (0);
}

t_env	*g_env = NULL;
