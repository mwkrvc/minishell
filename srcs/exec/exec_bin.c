#include "../../includes/minishell.h"

int	exit_with_code(int code)
{
	if (code == ENOENT)
		ft_putendl_fd("Command not found", STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (code == EACCES)
		exit(126);
	else if (code == EFAULT || code == ENOENT)
		exit (127);
	else
		exit (ERROR);
}

char	*absolute_path(char *bin)
{
	t_env	*env;
	char	*file;
	char	**paths;

	env = g_env;
	file = NULL;
	while (env && ft_strncmp(env->name, "PATH", 5))
		env = env->next;
	if (env)
	{
		paths = diff_split(env->value, ':');
		file = find_bin(paths, bin);
	}
	return (file);
}

int	exec_envvar(char **args, int status)
{
	char	*file;
	pid_t	pid;
	char	**envr;

	envr = list_to_array();
	file = absolute_path(args[0]);
	if (!file)
		file = ft_calloc(10, sizeof (int));
	pid = fork();
	command_signal();
	if (pid == 0)
	{
		execve(file, args, envr);
		exit_with_code(errno);
	}
	else if (pid < 0)
		exit(ERROR);
	else
	{
		wait(&status);
		free_arr(envr);
		if (file)
			free(file);
	}
	return (status);
}

int	exec_path(char **args)
{
	pid_t	pid;
	int		status;
	char	*exec[2];
	char	**envr;

	status = 0;
	exec[0] = args[0];
	exec[1] = NULL;
	envr = list_to_array();
	pid = fork();
	command_signal();
	if (pid == 0)
	{
		execve(exec[0], args, envr);
		exit_with_code(errno);
	}
	else if (pid < 0)
		exit(ERROR);
	else
	{
		wait(&status);
		free_arr(envr);
	}
	return (status);
}

int	ms_exec(char **args)
{
	char	*cmd;
	int		ret;

	cmd = args[0];
	if (ft_strchr(cmd, '/') || cmd[0] == '.')
		ret = exec_path(args);
	else
		ret = exec_envvar(args, 0);
	if (ret == 2)
		ret = 130;
	else if (ret == 3)
		ret = 131;
	return (ret);
}
