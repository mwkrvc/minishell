#include "../../includes/minishell.h"

void	ms_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC | S_IRWXU, 0777);
	if (fd == -1)
		return ;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		ft_putendl_fd(line, fd);
	}
}

void	redirect_doc(t_utils *utils)
{
	if (utils->fd_stdin)
		close(utils->fd_stdin);
	utils->fd_stdin = open(HEREDOC, O_RDONLY, 0777);
	if (utils->fd_stdin == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	dup2(utils->fd_stdin, STDIN_FILENO);
}

void	open_heredoc(t_token *token, t_utils *utils)
{
	t_token	*tok;

	(void)utils;
	tok = token;
	while (tok)
	{
		if (tok->type == R_HEREDOC)
			ms_heredoc(tok->args[0]);
		tok = tok->next;
	}
}
