#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_isseparator(char c)
{
	return ((c == '>' || c == '<' || c == '|' || c == ';'));
}

int	ft_isquotes(char c)
{
	return ((c == '\'' || c == '\"'));
}
