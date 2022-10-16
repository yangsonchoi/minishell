#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

typedef struct		s_data
{
	char			**envp;
	int				exit_status;
	bool			is_interactive;
}					t_data;


#endif