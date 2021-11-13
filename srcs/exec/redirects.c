#include "../../includes/minishell.h"

void	redirect_input(t_token *token, t_utils *utils)
{
	close(utils->fd_stdin);
	utils->fd_stdin = open(token->args[0], O_RDONLY, 0777);
	if (utils->fd_stdin == -1)
	{
		utils->no_exec = 1;
		ft_putstr_fd(token->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	dup2(utils->fd_stdin, STDIN_FILENO);
}

void	redirect_output(t_token *token, t_utils *utils)
{
	t_token	*temp;

	close(utils->fd_stdout);
	temp = token;
	if (token->type == R_TRUNC)
	{
		utils->fd_stdout = open(temp->args[0], O_CREAT
				| O_TRUNC | O_WRONLY, 0644);
		if (utils->fd_stdout == -1)
			ft_putendl_fd(strerror(errno), 2);
	}
	if (token->type == R_APPEND)
	{
		utils->fd_stdout = open(temp->args[0], O_CREAT
				| O_APPEND | O_WRONLY, 0644);
		if (utils->fd_stdout == -1)
			ft_putendl_fd(strerror(errno), 2);
	}
	dup2(utils->fd_stdout, STDOUT_FILENO);
	close(utils->fd_stdout);
}
