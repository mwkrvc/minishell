#include "../../includes/minishell.h"

void	wait_for_children(t_utils *utils)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < utils->pipes + 1)
	{
		pid = wait(&status);
		if (pid == utils->last)
		{
			if (status > 255)
				status = status % 255;
			exit_status(status);
		}
		i++;
	}
}

void	close_fds(int *fd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < 2 * num_pipes)
	{
		close(fd[i]);
		i++;
	}
}

void	parent_process(t_utils *utils, int *fd)
{
	close_fds(fd, utils->pipes);
	wait_for_children(utils);
	unlink(HEREDOC);
	free(fd);
}
