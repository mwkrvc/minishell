#include "../../includes/minishell.h"

void	unset_env(char *name)
{
	t_env	*env;
	t_env	*prev;

	env = g_env;
	if (env && !ft_strncmp(env->name, name, ft_strlen(name) + 1))
	{
		g_env = env->next;
		free(env);
		return ;
	}
	while (env && ft_strncmp(env->name, name, ft_strlen(name) + 1))
	{
		prev = env;
		env = env->next;
	}
	if (!env)
		return ;
	prev->next = env->next;
	free(env->name);
	free(env->value);
	free(env);
}

int	ms_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env(args[i]);
		i++;
	}
	return (0);
}
