#include "../../includes/minishell.h"

void	add_new_env(char *name, char *value)
{
	t_env	*new;
	t_env	*curr;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	curr = g_env;
	if (!curr)
		curr = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	(void)curr;
}

int	check_existing_env(char *name)
{
	t_env	*env;

	env = g_env;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name) + 1))
			return (1);
		env = env->next;
	}
	return (0);
}

int	not_valid_env(char *env)
{
	if (env && env[0] == '=')
	{
		ft_putendl_fd("export: `=': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	add_to_empty(char *name, char *value)
{
	t_env	*new;

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
	return (0);
}

int	ms_export(char **args)
{
	char		**new_env;
	int			iter_stat[2];

	if (!args[1])
		return (no_args());
	iter_stat[0] = 1;
	while (args[iter_stat[0]])
	{
		iter_stat[1] = not_valid_env(args[iter_stat[0]]);
		if (iter_stat[1])
		{
			iter_stat[0]++;
			continue ;
		}
		new_env = split_export(args[iter_stat[0]]);
		if (check_existing_env(new_env[0]))
			change_env_value(new_env[0], new_env[1]);
		else if (!g_env)
			add_to_empty(new_env[0], new_env[1]);
		else
			add_new_env(new_env[0], new_env[1]);
		free_arr(new_env);
		iter_stat[0]++;
	}
	return (iter_stat[1]);
}
