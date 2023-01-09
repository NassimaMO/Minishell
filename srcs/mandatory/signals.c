#include "minishell.h"

void    ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		print_shell();
	}
}

void	control_c(void)
{
	struct sigaction    sa;

	sa.sa_handler = &ft_handler;
	sigaction(SIGINT, &sa, NULL);
}
