#include "../../includes/minishell.h"

int	pass_space(char *input, t_qout *tmp)
{
	while (input[tmp->i] != '\0' && tmp->quot == 0 && ft_isspace(input[tmp->i]))
		tmp->i++;
	tmp->start = tmp->i;
	return (1);
}

int	pass_letter_2(char *input, t_list **list, t_qout *tmp)
{
	char	*tmp_con;

	if (input[tmp->i] == '$' && tmp->quot == 0)
	{
		tmp_con = tmp->content;
		tmp->content = ft_substr(input, tmp->start, (tmp->i - tmp->start));
		if (tmp_con)
			free(tmp_con);
		parse_env_3(tmp, input, list);
		return (1);
	}
	if ((tmp->quot == 0 && input[tmp->i] == '\0' && tmp->start < tmp->i)
		|| (tmp->quot == 0 && tmp->start < tmp->i && ft_is_some(input[tmp->i])))
	{
		tmp_con = tmp->content;
		tmp->content = ft_substr(input, tmp->start, (tmp->i - tmp->start));
		if (tmp_con)
			free(tmp_con);
		ft_lstadd_back(list, ft_lstnew(ft_strdup(tmp->content)));
		free_tmp(tmp);
	}
	return (0);
}

int	pass_letter(char *input, t_list **list, t_qout *tmp)
{
	tmp->start = tmp->i;
	check_quotes(&tmp->quot, input[tmp->i]);
	while (tmp->quot == 0 && (!(ft_is_some(input[tmp->i]))
			|| ft_is_some(input[tmp->i]) == 3))
	{
		check_quotes(&tmp->quot, input[tmp->i]);
		if (input[tmp->i] == ';')
			return (0);
		if (tmp->quot != 0)
		{
			tmp->content = ft_substr(input, tmp->start, (tmp->i - tmp->start));
			break ;
		}
		tmp->i++;
	}
	pass_letter_2(input, list, tmp);
	return (1);
}
