#include "../../includes/minishell.h"

int	exit_status(int code)
{
	static int	ret;

	if (code == -1)
		return (ret);
	else
		ret = code;
	(void)ret;
	return (0);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}
