#include "minishell.h"

void	set_terminal(int option)
{
	struct termios			tty;
	static struct termios	tmp;

	if (option == SET)
	{
		tcgetattr(STDIN_FILENO, &tty);
		tmp = tty;
		//tty.c_lflag &= ~ECHO;
		//tty.c_lflag &= ~ICANON;
		tty.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	else if (option == RESET)
		return ((void)tcsetattr(STDIN_FILENO, TCSANOW, &tmp));
}
