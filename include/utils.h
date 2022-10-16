#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <stdbool.h>

/*
** error.c
*/
void	print_error(char *cmd, char *input, bool err_status);

/*
** envp_add_change.c
*/
void	add_envp(t_data *data, char * variable, char *value);
void	change_envp(t_data *data, char* variable, char *value);

/*
** envp_remove_print.c
*/
void	remove_envp(t_data *data, char *remove);
void	print_envp(t_data *data, char *str);

#endif