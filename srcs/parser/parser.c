#include "../../includes/minishell.h"

t_token	*no_type(t_token *t, t_list **list)
{
	free_all_tokens(t);
	ft_lstclear(list, free);
	return (NULL);
}

t_token	*put_to_tokens(t_list **list)
{
	t_token					*t;
	t_list					*l;
	t_token					*cmd;
	int						type;
	t_add					add_token[6];

	t = NULL;
	l = *list;
	cmd = NULL;
	type = 0;
	add_token[0] = add_r_tkn;
	add_token[1] = add_r_tkn;
	add_token[2] = add_r_tkn;
	add_token[3] = add_r_tkn;
	add_token[4] = add_pipe_tkn;
	add_token[5] = add_c_token;
	while (l)
	{
		type = find_type_separator(l);
		if ((add_token[type](&t, &l, &cmd)) == NULL)
			return ((no_type(t, list)));
		l = l->next;
	}
	return (t);
}

void	init_tmp(t_qout *tmp)
{
	tmp->i = 0;
	tmp->start = 0;
	tmp->content = NULL;
	tmp->quot = 0;
}

int	parse_input_while(char *input, t_list **list, t_qout *tmp)
{
	while (input[tmp->i] != '\0')
	{
		pass_space(input, tmp);
		if (!(pass_letter(input, list, tmp)))
		{
			ft_error(NULL, "syntax error ';'");
			return (0);
		}
		if (tmp->quot != 0)
		{
			if (!meet_quot(input, list, tmp))
				return (0);
		}
		if (input[tmp->i] == ';')
		{
			ft_error(NULL, "syntax error ';'");
			return (0);
		}
		while (input[tmp->i] == '$' && tmp->quot == 0)
			parse_env_3(tmp, input, list);
		if (ft_isseparator(input[tmp->i]) && tmp->quot == 0)
			tmp->i = parse_separator(input, tmp->i, list);
	}
	return (1);
}

t_list	*parse_input(char *input)
{
	t_list	*list;
	t_qout	tmp;

	list = NULL;
	init_tmp(&tmp);
	while (input[tmp.i] != '\0')
	{
		if (!(parse_input_while(input, &list, &tmp)))
			return (NULL);
	}
	free_tmp(&tmp);
	return (list);
}
