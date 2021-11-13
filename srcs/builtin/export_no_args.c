#include "../../includes/minishell.h"

void	swap_elems(t_env *a, t_env *b)
{
	char	*name;
	char	*value;

	name = a->name;
	value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = name;
	b->value = value;
}

t_env	*sort_no_args(int swap)
{
	t_env	*temp1;
	t_env	*temp2;
	t_env	*env;

	env = g_env;
	if (!env)
		return (NULL);
	temp2 = NULL;
	while (swap)
	{
		swap = 0;
		temp1 = env;
		while (temp1->next != temp2)
		{
			if (temp1->name[0] > temp1->next->name[0])
			{
				swap_elems(temp1, temp1->next);
				swap = 1;
			}
			temp1 = temp1->next;
		}
		temp2 = temp1;
	}
	return (env);
}

int	no_args(void)
{
	t_env	*env;
	char	**save_env;
	int		swap;

	swap = 1;
	save_env = list_to_array();
	env = sort_no_args(swap);
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->name, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
	free_all_env();
	init_env(save_env);
	free_arr(save_env);
	return (0);
}
