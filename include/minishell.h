#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

int					g_exit_status;

typedef struct		s_data
{
	char			**envp;
	bool			is_interactive;
}					t_data;


#endif