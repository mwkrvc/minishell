#include "../../includes/minishell.h"

void	*free_all_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		if (g_env->name)
			free(g_env->name);
		if (g_env->value)
			free(g_env->value);
		tmp = g_env->next;
		free(g_env);
		g_env = tmp;
	}
	return (g_env);
}

void	free_all_tokens(t_token *token_list)
{
	t_token	*tmp;
	int		i;

	while (token_list)
	{
		i = 0;
		if (token_list->args)
		{
			while (token_list->args[i])
			{
				free(token_list->args[i]);
				i++;
			}
		}
		tmp = token_list->next;
		free(token_list->args);
		free(token_list);
		token_list = tmp;
	}
}

void	free_tmp(t_qout *tmp)
{
	if (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		tmp->content = NULL;
	}
}

void	main_free(t_token *token_list, t_list *list,
				  char *cmd_line, t_utils *utils)
{
	reset_fds(utils);
	if (cmd_line)
		free(cmd_line);
	free_all_tokens(token_list);
	ft_lstclear(&list, free);
}
