#include "../../includes/minishell.h"

void	free_symbols_strs(char **symbols_strs)
{
	int	i;

	i = 0;
	while (symbols_strs[i])
	{
		free(symbols_strs[i]);
		i++;
	}
	free(symbols_strs);
}

int	find_type_separator(t_list *l)
{
	int		x;
	int		j;
	char	**symbols_strs;

	symbols_strs = ft_split(">> << > < |", ' ');
	x = 0;
	j = 0;
	while (symbols_strs[x])
	{
		j = ft_strlen(symbols_strs[x]);
		if ((ft_strncmp(l->content, symbols_strs[x], j)) == 0)
		{
			free_symbols_strs(symbols_strs);
			return (x);
		}
		x++;
	}
	free_symbols_strs(symbols_strs);
	return (x);
}

void	push_content(char **content, t_list **list)
{
	t_list	*new;

	new = NULL;
	new = ft_lstnew(*content);
	ft_lstadd_back(list, new);
}

int	parse_separator(char *input, int i, t_list **list)
{
	int		x;
	int		j;
	char	*content;
	char	**symbols_strs;

	x = 0;
	j = 0;
	content = NULL;
	symbols_strs = ft_split(">> << > < |", ' ');
	if (ft_isseparator(input[i]))
	{
		while (symbols_strs[x])
		{
			j = ft_strlen(symbols_strs[x]);
			if ((ft_strncmp(&input[i], symbols_strs[x], j)) == 0)
			{
				content = ft_substr(input, i, j);
				push_content(&content, list);
				break ;
			}
			x++;
		}
	}
	free_symbols_strs(symbols_strs);
	return (i + j);
}
