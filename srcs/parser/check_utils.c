#include "../../includes/minishell.h"

int	ft_is_some(char c)
{
	if (c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	else if (c == '>' || c == '<' || c == '|')
		return (2);
	else if (c == '\'' || c == '"')
		return (3);
	else if (c == '\0')
		return (4);
	else if (c == '$')
		return (5);
	return (0);
}

int	ft_is_new_token(char c)
{
	if ((ft_is_some(c)) == 1 || (ft_is_some(c)) == 2 || (ft_is_some(c)) == 4)
		return (1);
	return (0);
}

int	check_quotes(char *q, char c)
{
	if ((c == '\'' || c == '"') && *q == 0)
	{
		*q = c;
		return (1);
	}
	else if ((c == '\'' && *q == '\'') || (c == '"' && *q == '"'))
	{
		*q = 0;
		return (0);
	}
	return (0);
}
