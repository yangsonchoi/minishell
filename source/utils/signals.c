#include "utils.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>

static void	sig_handler(int	sig);

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
}

static void	sig_handler(int	sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_exit_status = sig;
}