#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

void    builtin_env(char **cmd, t_data *data)
{
    if (cmd[1] != NULL)
    {
        print_error(cmd[0], "usage: pwd with no options or arguments", NULL);
        data->exit_status = 1;
    }
    else
    {
        print_env(data, NULL);
        data->exit_status = 0;
    }
}