#include "../../includes/minishell.h"

int	close_quot(char *input, t_list **list, t_qout *tmp)
{
	t_list	*new;

	check_quotes(&tmp->quot, input[tmp->i]);
	if ((tmp->start < tmp->i) || (input[tmp->i] == '\''))
		join_substr(input, tmp);
	if (tmp->start >= tmp->i && tmp->content == NULL)
		return (0);
	new = ft_lstnew(ft_strdup(tmp->content));
	ft_lstadd_back(list, new);
	free_tmp(tmp);
	return (1);
}

int	glue_aft_quot(char *input, t_list **list, t_qout *tmp)
{
	check_quotes(&tmp->quot, input[tmp->i]);
	if (tmp->start < tmp->i)
		join_substr(input, tmp);
	tmp->i++;
	while ((ft_is_some(input[tmp->i])) == 5)
	{
		tmp->start = tmp->i;
		parse_env_3(tmp, input, list);
		tmp->start = tmp->i;
	}
	if ((ft_is_some(input[tmp->i])) == 3)
	{
		check_quotes(&tmp->quot, input[tmp->i]);
		tmp->i = tmp->i + 1;
		tmp->start = tmp->i;
	}
	else if (tmp->quot == 0 && !(ft_is_some(input[tmp->i])))
	{
		tmp->start = tmp->i;
		while (!(ft_is_some(input[tmp->i])))
			tmp->i++;
	}
	return (tmp->i);
}

void	parse_quot_cond_3(char *input, t_list **list, t_qout *tmp)
{
	if (tmp->start < tmp->i)
		join_substr(input, tmp);
	parse_env_3(tmp, input, list);
}

int	parse_quot(char *input, t_list **list, t_qout *tmp)
{
	if (tmp->start < tmp->i)
		join_substr(input, tmp);
	while (input[tmp->i] != tmp->quot && input[tmp->i] != '\0')
	{
		check_quotes(&tmp->quot, input[tmp->i]);
		while (quotes_condition_2(input, tmp))
			tmp->i++;
		while (tmp->quot != '\'' && input[tmp->i] == '$')
			parse_quot_cond_3(input, list, tmp);
		if ((input[tmp->i] == tmp->quot)
			&& !(ft_is_new_token(input[tmp->i + 1])))
			glue_aft_quot(input, list, tmp);
		if ((ft_is_some(input[tmp->i])) == 3 && tmp->quot == 0)
			new_quot(input, tmp);
		if (tmp->quot == 0 && ft_is_new_token(input[tmp->i]))
			break ;
	}
	while (tmp->start == tmp->i && tmp->content != NULL
		&& input[tmp->i] == tmp->quot && !(ft_is_new_token(input[tmp->i + 1])))
		glue_aft_quot(input, list, tmp);
	if (quot_condition_1(tmp, input) || input[tmp->i] == tmp->quot)
		close_quot(input, list, tmp);
	return (tmp->i);
}

int	meet_quot(char *input, t_list **list, t_qout *tmp)
{
	tmp->i_q = 1;
	if (input[tmp->i] == tmp->quot)
	{
		tmp->i++;
		tmp->start = tmp->i;
	}
	else
		tmp->start = tmp->i;
	parse_quot(input, list, tmp);
	if (tmp->quot != 0)
	{
		ft_error(NULL, "syntax error: unclosed quote");
		return (0);
	}
	if (input[tmp->i] == '\0')
		return (1);
	if ((ft_is_some(input[tmp->i]) == 3))
		tmp->i += 1;
	pass_space(input, tmp);
	return (1);
}
