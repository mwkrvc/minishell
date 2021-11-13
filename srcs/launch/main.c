#include "../../includes/minishell.h"

void	save_fds(t_utils *utils)
{
	utils->fd_stdin = -21;
	utils->fd_stdout = -21;
	utils->save_in = dup(STDIN_FILENO);
	utils->save_out = dup(STDOUT_FILENO);
	utils->exit = 1;
}

void	start_shell(char **envp, t_utils *utils, int ac, char **av)
{
	char	*level;
	int		lvl;
	char	*temp;

	(void)ac;
	(void)av;
	init_env(envp);
	unset_env("OLDPWD");
	level = env_value("SHLVL");
	if (!level)
		add_new_env("SHLVL", "1");
	else
	{
		lvl = ft_atoi(level);
		temp = ft_itoa(lvl + 1);
		change_env_value("SHLVL", temp);
		free(temp);
	}
	save_fds(utils);
}

void	reset_fds(t_utils *utils)
{
	dup2(utils->save_in, 0);
	dup2(utils->save_out, 1);
	close(utils->save_out);
	close(utils->save_out);
	utils->save_out = dup(1);
	utils->save_in = dup(0);
}

void	first_argument_space(t_list **list, t_token **token_list)
{
	ft_lstclear(list, free);
	*list = parse_input((*token_list)->args[0]);
	free_all_tokens(*token_list);
	*token_list = put_to_tokens(list);
}

int	main(int ac, char **av, char **envp)
{
	char		*cmd_line;
	t_token		*token_list;
	t_list		*list;
	t_utils		utils;

	cmd_line = NULL;
	start_shell(envp, &utils, ac, av);
	while (utils.exit)
	{
		main_signal();
		cmd_line = readline("minishell: ");
		if (cmd_line == NULL)
			cmd_line = handle_ctrl_d();
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		list = parse_input(cmd_line);
		token_list = put_to_tokens(&list);
		if (token_list && ft_strchr(token_list->args[0], ' ')
			&& cmd_line[0] == '$')
			first_argument_space(&list, &token_list);
		tokens(token_list, &utils);
		main_free(token_list, list, cmd_line, &utils);
	}
	free_all_env();
	return (exit_status(-1));
}
