#include "builtin.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void    builtin_exit(char **cmd, t_data *data)
{
    if (cmd[1] = NULL)
        exit(data->exit_status);
    data->exit_status = ft_atoi(cmd[1]);
    exit(data->exit_status);
}