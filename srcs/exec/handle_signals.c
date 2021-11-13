#include "../../includes/minishell.h"

void	bin_ctrl_c(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	exit_status(130);
}

void	bin_ctrl_4(int signo)
{
	(void)signo;
	printf("Quit: 3\n");
	exit_status(131);
}

void	command_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, bin_ctrl_4);
	signal(SIGINT, bin_ctrl_c);
}

void	heredoc_ctrl_c(int signo)
{
	(void)signo;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	exit(1);
}
