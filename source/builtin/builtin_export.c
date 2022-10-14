#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include <errno.h>

void    builtin_export(char **cmd, t_data *data)
{
    int     i;    
    char    *new_cmd;
    if (cmd[0] == NULL)
        print_envp(data->envp, "declare -x");
    else
    {
        i = 1;
        data->exit_status = 0;
        while (cmd[i] != NULL)
        {
            new_cmd = parse_export_cmd(cmd[i]);
            if (new_cmd == NULL)
            {
                errno = 22;
                print_error(cmd[0], cmd[i], true);
                data->exit_status = 1;
            }
            else
            {
                if (is_variable_exist(cmd[i]) == true)
                    change_envp(data, new_cmd);
                else
                    add_envp(data, new_cmd);
            }
        }
    }
}

static char *parse_export_cmd(char *old_cmd)
{
    char    *new_cmd;
    char    *temp;

    temp = ft_strchr(old_cmd, '=');
}