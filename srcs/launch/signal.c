#include "../../includes/minishell.h"

void	handle_ctrl_c(int i)
{
	(void)i;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	exit_status(130);
}

char	*handle_ctrl_d(void)
{
	char	*cmd_line;

	cmd_line = ft_strdup("exit");
	exit_status(131);
	return (cmd_line);
}

void	main_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
