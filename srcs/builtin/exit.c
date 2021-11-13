#include "../../includes/minishell.h"

int	isint(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i++]) == 0)
			return (0);
	}
	return (1);
}

int	exit_error(char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putendl_fd(" numeric argument required", STDERR_FILENO);
	return (255);
}

int	ms_exit(char **args, t_utils *utils)
{
	int	i;
	int	code;

	utils->exit = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	i = 0;
	while (args[i])
		i++;
	if (i == 2)
	{
		code = ft_atoi(args[1]);
		if (!isint(args[1]))
			return (exit_error(args[0]));
		else
			return (code);
	}
	else if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		utils->exit = 1;
		return (1);
	}
	return (0);
}
