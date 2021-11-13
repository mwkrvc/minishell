#include "../../includes/minishell.h"

t_token	*process_redirects(t_token *token, t_utils *utils)
{
	t_token	*tok;
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	tok = token;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == COMMAND)
		{
			new->type = COMMAND;
			new->args = tok->args;
			new->next = NULL;
		}
		else if (tok->type == R_TRUNC || tok->type == R_APPEND)
			redirect_output(tok, utils);
		else if (tok->type == R_INPUT)
			redirect_input(tok, utils);
		else if (tok->type == R_HEREDOC)
			redirect_doc(utils);
		tok = tok->next;
	}
	rearrange_token(&tok, new);
	return (token);
}

int 	child_process(t_token *token, t_utils *utils, int *fds, int fd_iter)
{
	int	status;

	utils->no_exec = 0;
	if (find_pipe(token))
		dup_smth(fds[fd_iter + 1], 1);
	if (token->prev)
		dup_smth(fds[fd_iter - 2], 0);
	token = process_redirects(token, utils);
	close_fds(fds, utils->pipes);
	if (!utils->no_exec)
		status = execute_commands(token->args, utils);
	else
		status = 1;
	exit(status);
}

int	*open_pipes(t_token *token, t_utils *utils)
{
	int	i;
	int	*fd;

	i = 0;
	utils->pipes = pipes_num(token);
	fd = ft_calloc(2 * utils->pipes, sizeof (int));
	while (i < utils->pipes)
	{
		if (pipe(fd + i * 2) < 0)
			return (0);
		i++;
	}
	return (fd);
}

void	pipe_exec(t_token *token, t_utils *utils)
{
	pid_t	pid;
	int		*fd;
	int		fd_iter;

	fd = open_pipes(token, utils);
	fd_iter = 0;
	while (token)
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
			child_process(token, utils, fd, fd_iter);
		token = next_command(token);
		if (fd_iter == utils->pipes * 2)
			utils->last = pid;
		fd_iter +=2;
	}
	parent_process(utils, fd);
}
