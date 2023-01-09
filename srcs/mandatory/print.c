#include "minishell.h"

void	print_shell(void)
{
	char	*user_name;
	char	*computer_name;
	char	*path;

	user_name = getenv("USER");
	if (!user_name)
		user_name = "";
	computer_name = "";
	path = "";
	ft_putstr_fd(user_name, STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(computer_name, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('$', STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
}
