#include "../../includes/minishell.h"

char	*get_value_from_env(char *key)
{
	t_env	*tmp;
	int		len_k;
	int		len_n;

	tmp = g_env;
	if (!key || !tmp || !key[0])
		return (NULL);
	while (tmp != NULL)
	{
		len_k = ft_strlen(key);
		len_n = ft_strlen(tmp->name);
		if (len_k == len_n
			&& !(ft_strncmp(key, tmp->name, ft_strlen(tmp->name))))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	question_env(t_qout *tmp)
{
	char	*exit_stat;
	char	*tmp_con;

	exit_stat = ft_itoa(exit_status(-1));
	tmp_con = tmp->content;
	tmp->content = ft_strjoin(tmp->content, exit_stat);
	if (tmp_con)
	{
		free(tmp_con);
		free(exit_stat);
	}
	tmp->i++;
	return (tmp->i);
}

int	parse_env_end(t_qout *tmp, char *input, t_list **list)
{
	while ((!(ft_is_some(input[tmp->i])))
		|| (input[tmp->i] == '\'' && tmp->quot == '"')
		|| (tmp->quot != 0 && (ft_is_some(input[tmp->i])) == 1))
		tmp->i++;
	if (tmp->start < tmp->i)
	{
		join_substr(input, tmp);
		tmp->start = tmp->i;
	}
	if (ft_is_new_token(input[tmp->i]) && tmp->content[0] != '\0')
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(tmp->content)));
		free_tmp(tmp);
	}
	return (1);
}

int	parse_env_3(t_qout *tmp, char *input, t_list **list)
{
	char	*key;

	key = NULL;
	tmp->i++;
	tmp->start = tmp->i;
	if (input[tmp->i] == '?')
	{
		question_env(tmp);
	}
	while (input[tmp->i] != '\0' && (ft_isalnum(input[tmp->i])
			|| input[tmp->i] == '_'))
		tmp->i++;
	if (!(ft_isalnum(input[tmp->i])))
	{
		key = ft_substr(input, tmp->start, (tmp->i - tmp->start));
		if (!key[0])
			tmp->content = ft_strjoin(tmp->content, ft_strdup("$"));
	}
	tmp_join_free(tmp, key);
	if (key[0] != '\0')
		free(key);
	parse_env_end(tmp, input, list);
	return (tmp->i);
}
