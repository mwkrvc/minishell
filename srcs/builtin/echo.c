#include "../../includes/minishell.h"

int	echo_two(char **args)
{
	if (!(ft_strncmp(args[1], "-n", 3)))
		return (0);
	else
	{
		ft_putendl_fd(args[1], STDOUT_FILENO);
		return (0);
	}
}

void	put_args(char **args, int start, int num)
{
	while (args[start])
	{
		ft_putstr_fd(args[start], STDOUT_FILENO);
		if (start != num - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		start++;
	}
}

int	ms_echo(char **args)
{
	int	start;
	int	eol;
	int	num;

	num = 0;
	while (args[num])
		num++;
	if (num < 2)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else if (num == 2)
		return (echo_two(args));
	start = 1;
	eol = 1;
	while (!ft_strncmp(args[start], "-n", 3))
	{
		start++;
		eol = 0;
	}
	put_args(args, start, num);
	if (eol == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
