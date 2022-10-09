#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"

typedef struct  s_cmd
{
    char        **cmd;
    t_token     **redirect;
    int         pipe_fd[2];
}               t_cmd;

/*
** execute.c
*/

void    execute_line(t_token_list *token_list);

/*
** execute_token.c
*/
void token_to_command(t_token_list *token_list, t_cmd **cmd_list);

#endif