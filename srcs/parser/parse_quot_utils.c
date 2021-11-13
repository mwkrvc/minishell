#include "../../includes/minishell.h"

int	quot_condition_1(t_qout *tmp, char *input)
{
	if ((((input[tmp->i] == tmp->quot) || (tmp->quot == 0)
				|| (input[tmp->i] == '\0'))
			&& (ft_is_new_token(input[tmp->i + 1])))
		|| (tmp->quot == 0 && ft_is_new_token(input[tmp->i])))
		return (1);
	return (0);
}

int	quotes_condition_2(char *input, t_qout *tmp)
{
	if ((ft_is_some(input[tmp->i])) == 1
		|| (ft_is_some(input[tmp->i])) == 2
		|| ((ft_is_some(input[tmp->i])) == 5 && tmp->quot == '\'')
		|| !(ft_is_some(input[tmp->i]))
		|| ((ft_is_some(input[tmp->i])) == 3 && input[tmp->i] != tmp->quot))
		return (1);
	return (0);
}

void	tmp_join_free(t_qout *tmp, char *key)
{
	char	*str;
	char	*tmp_con;

	str = ft_strdup(get_value_from_env(key));
	tmp_con = tmp->content;
	tmp->content = ft_strjoin(tmp->content, str);
	tmp->start = tmp->i;
	if (str && tmp_con)
	{
		free(str);
		free(tmp_con);
	}
}

void	join_substr(char *input, t_qout *tmp)
{
	char	*str;
	char	*tmp_con;

	str = ft_substr(input, tmp->start, (tmp->i - tmp->start));
	tmp_con = tmp->content;
	tmp->content = ft_strjoin(tmp->content, str);
	if (tmp_con)
	{
		free(str);
		free(tmp_con);
	}
}

void	new_quot(char *input, t_qout *tmp)
{
	if (tmp->start < tmp->i)
		join_substr(input, tmp);
	check_quotes(&tmp->quot, input[tmp->i]);
	tmp->i++;
	tmp->start = tmp->i;
}
