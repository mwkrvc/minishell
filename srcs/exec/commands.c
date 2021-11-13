#include "../../includes/minishell.h"

int	convert_status(int st)
{
	int	status;

	status = st;
	if (status > 255 || status < 0)
		status = status % 255;
	return (status);
}

int	execute_commands(char **args, t_utils *utils)
{
	int	status;

	if (!args)
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		status = ms_echo(args);
	else if (!ft_strncmp(args[0], "pwd", 4))
		status = ms_pwd();
	else if (!ft_strncmp(args[0], "export", 7))
		status = ms_export(args);
	else if (!ft_strncmp(args[0], "env", 4))
		status = ms_env();
	else if (!ft_strncmp(args[0], "exit", 5))
		status = ms_exit(args, utils);
	else if (!ft_strncmp(args[0], "unset", 6))
		status = ms_unset(args);
	else if (!ft_strncmp(args[0], "cd", 3))
		status = ms_cd(args[1]);
	else
		status = ms_exec(args);
	status = convert_status(status);
	exit_status(status);
	return (status);
}

char	*lwr_s(char *str)
{
	int		i;
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len])
		len++;
	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = (char)ft_tolower(str[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	basic_exec(t_token *token, t_utils *utils)
{
	char	**args;

	utils->no_exec = 0;
	while (token)
	{
		if (token->type == COMMAND)
			args = token->args;
		else if (token->type == R_INPUT)
			redirect_input(token, utils);
		else if (token->type == R_TRUNC || token->type == R_APPEND)
			redirect_output(token, utils);
		else if (token->type == R_HEREDOC)
			redirect_doc(utils);
		token = token->next;
	}
	unlink(HEREDOC);
	if (!utils->no_exec)
		execute_commands(args, utils);
	else
		exit_status(1);
}

void	tokens(t_token *token, t_utils *utils)
{
	pid_t	pid;
	int		status;

	utils->no_exec = 0;
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_ctrl_c);
		open_heredoc(token, utils);
		exit(0);
	}
	else
	{
		wait(&status);
		if (status != 256)
		{
			if (find_pipe(token))
				pipe_exec(token, utils);
			else
				basic_exec(token, utils);
		}
		else
			exit_status(1);
	}
}
