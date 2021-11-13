#include "../../includes/minishell.h"

t_token	*ft_token_new(enum e_token_type type, char **args)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!(token))
		return (NULL);
	token->type = type;
	token->args = args;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_tklast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_tkadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = ft_tklast(*lst);
		last->next = new;
		new->prev = last;
	}
}
