#include "../../includes/minishell.h"

int	find_pipe(t_token *token)
{
	t_token	*tok;

	tok = token;
	while (tok)
	{
		if (tok->type == PIPE)
			return (1);
		tok = tok->next;
	}
	return (0);
}

t_token	*next_command(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		token = token->next;
	return (token);
}

void	dup_smth(int fildes, int fildes2)
{
	if (dup2(fildes, fildes2) < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(ERROR);
	}
}

void	rearrange_token(t_token **token, t_token *new)
{
	if (token && new)
	{
		new->next = *token;
		*token = new;
	}
}

int	pipes_num(t_token *token)
{
	t_token	*tok;
	int		cnt;

	tok = token;
	cnt = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			cnt++;
		tok = tok->next;
	}
	return (cnt);
}
