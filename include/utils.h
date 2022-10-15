#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

/*
** error.c
*/
void    print_error(char *cmd, char *input, bool err_status);

/*
** envp.c
*/
void	add_envp(t_data *data, char *add_envp);
void    remove_envp(t_data *data, char *remove);
void    print_envp(t_data *data, char *str);

#endif