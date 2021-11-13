#include "../../includes/minishell.h"

char	*env_value(char *name)
{
	t_env	*env;

	env = g_env;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name) + 1))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (env->value);
}

char	*cd_no_args(void)
{
	t_env	*env;

	env = g_env;
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*odd_cases(char *new_dir)
{
	if (!new_dir)
	{
		new_dir = cd_no_args();
		{
			if (!new_dir)
			{
				ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
				return (NULL);
			}
		}
	}
	if (!ft_strncmp(new_dir, "-", 2))
	{
		new_dir = env_value("OLDPWD");
		if (!new_dir)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(env_value("OLDPWD"), STDOUT_FILENO);
	}
	return (new_dir);
}

int	chdir_error(char *new_dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)new_dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

int	ms_cd(char *new_dir)
{
	char	*cwd;
	char	*pwd;
	char	*oldpwd;

	new_dir = odd_cases(new_dir);
	if (!new_dir)
		return (1);
	if (chdir(new_dir) == -1)
		return (chdir_error(new_dir));
	oldpwd = env_value("PWD");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(cwd);
		return (1);
	}
	change_env_value("OLDPWD", oldpwd);
	pwd = cwd;
	change_env_value("PWD", pwd);
	free(cwd);
	return (0);
}
