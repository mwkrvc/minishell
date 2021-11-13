#include "../../includes/minishell.h"

int	list_len(void)
{
	t_env	*env;
	int		i;

	i = 0;
	env = g_env;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*diff_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	temp = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (temp);
}

char	**list_to_array(void)
{
	t_env	*env;
	t_env	*curr;
	char	**arr;
	int		i;
	char	*name_eq;

	env = g_env;
	curr = env;
	arr = (char **) malloc(sizeof (char *) * (list_len() + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (curr)
	{
		name_eq = diff_strjoin(curr->name, "=");
		arr[i] = diff_strjoin(name_eq, curr->value);
		if (!arr[i])
			arr[i] = name_eq;
		else
			free(name_eq);
		curr = curr->next;
		i++;
	}
	arr[i] = (void *)0;
	return (arr);
}
