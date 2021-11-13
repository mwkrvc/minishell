#include "../../includes/minishell.h"

void	ft_error(char *arg, char *error_msg)
{
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	if (arg && error_msg)
		ft_putstr_fd(": ", STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
}
