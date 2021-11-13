#include "../../includes/minishell.h"

void	change_env_value(char *name, char *value)
{
	t_env	*env;

	env = g_env;
	while (env && ft_strncmp(env->name, name, ft_strlen(name) + 1))
		env = env->next;
	if (env)
	{
		free(env->value);
		env->value = NULL;
		env->value = ft_strdup(value);
	}
	if (!env && !ft_strncmp(name, "OLDPWD", 7))
		add_new_env(name, value);
}
