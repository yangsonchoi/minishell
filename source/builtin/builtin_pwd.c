#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void    builtin_pwd(char **cmd, t_data *data)
{
    char    *pwd;
    int     i;

    if (cmd[1] != NULL)
    {
        print_error()
        data->exit_status = 1;
    }
    else
    {
        pwd = getcwd(NULL, 0);
        printf("%s\n", pwd);
        free(pwd);
        data->exit_status = 0
    }
}