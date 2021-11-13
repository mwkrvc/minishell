#include "../../includes/minishell.h"

t_token	*add_c_token(t_token **t, t_list **e, t_token **curr)
{
	t_token	*new_t;
	char	*str;

	if (curr && *curr)
	{
		new_t = *curr;
		str = ft_strdup((*e)->content);
		new_t->args = ft_arraypush(new_t->args, str);
		free(str);
		return (*curr);
	}
	str = ft_strdup((*e)->content);
	new_t = ft_token_new(COMMAND, ft_arraypush(NULL, str));
	free(str);
	ft_tkadd_back(t, new_t);
	*curr = new_t;
	return (new_t);
}

t_token	*add_r_tkn(t_token **t_lst, t_list **e, t_token **curr)
{
	t_token			*token;
	unsigned int	type;
	char			*str;

	(void)curr;
	token = NULL;
	if ((*e)->next == NULL || find_type_separator((*e)->next) != 5)
		return (NULL);
	if ((*e)->prev == NULL && (*e)->next && (*e)->next->next)
	{
		*curr = ft_token_new(COMMAND, NULL);
		ft_tkadd_back(t_lst, *curr);
	}
	type = find_type_separator(*e) + 1;
	str = ft_strdup((*e)->next->content);
	token = ft_token_new(type, ft_arraypush(NULL, str));
	free(str);
	ft_tkadd_back(t_lst, token);
	*e = (*e)->next;
	return (token);
}

t_token	*add_pipe_tkn(t_token **t, t_list **e, t_token **curr)
{
	t_token	*new;
	t_token	*token;
	t_token	*last_token;

	*curr = NULL;
	new = ft_tklast(*t);
	if (new)
		last_token = *t;
	else
		last_token = NULL;
	if (last_token == NULL || last_token->type > R_INPUT || (*e)->next == NULL)
	{
		ft_error(NULL, "syntax error near token '|'");
		return (NULL);
	}
	token = ft_token_new(PIPE, NULL);
	ft_tkadd_back(t, token);
	return (token);
}
