#include "../../includes/minishell.h"

char	*path_return(char *path, char *binn, DIR *dir)
{
	free(binn);
	closedir(dir);
	return (path);
}

char	*find_dir(char **paths, char *bin, int i, char *binn)
{
	DIR				*dir;
	struct dirent	*ent;

	while (paths[i])
	{
		dir = opendir(paths[i]);
		if (dir)
		{
			ent = readdir(dir);
			while (ent)
			{
				binn = lwr_s(bin);
				if (!ft_strncmp(ent->d_name, bin, ft_strlen(bin) + 1)
					|| !ft_strncmp(ent->d_name, binn, ft_strlen(bin) + 1))
					return (path_return(paths[i], binn, dir));
				free(binn);
				ent = readdir(dir);
			}
			closedir(dir);
			i++;
		}
		else
			return (NULL);
	}
	return (NULL);
}

char	*find_bin(char **paths, char *bin)
{
	char	*dir;
	char	*temp;
	char	*ret;
	int		i;

	i = 0;
	dir = find_dir(paths, bin, i, NULL);
	if (!dir)
	{
		free_arr(paths);
		return (NULL);
	}
	temp = ft_strjoin(dir, "/");
	ret = ft_strjoin(temp, bin);
	if (temp)
		free(temp);
	free_arr(paths);
	return (ret);
}
