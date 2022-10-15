#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include "parse.h"
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

void    builtin_export(char **cmd, t_data *data)
{
    int     i;    
    char    *new_cmd;

    if (cmd[1] == NULL)
        print_envp(data->envp, "declare -x");
    else
    {
        i = 1;
        data->exit_status = 0;
        while (cmd[i] != NULL)
        {
            new_cmd = parse_export_cmd(cmd[i], data);
            if (new_cmd == NULL)
            {
                errno = 22;
                print_error(cmd[0], cmd[i], true);
                data->exit_status = 1;
            }
            else
                add_or_change_envp(new_cmd, data);
        }
        i++;
    }
}

static char *parse_export_cmd(char *old_cmd, t_data *data)
{
    char    *new_cmd;
    char    *equal_sign;
    char    *temp;
    t_token temp_token;

    equal_sign = ft_strchr(old_cmd, '=');
    if (equal_sign == NULL)
        return (old_cmd);
    if (equal_sign == old_cmd)
        return (NULL);

    temp = ft_substr(old_cmd, 0, equal_sign - old_cmd);
    new_cmd = ft_strjoin(temp, "\"");
    free(temp);
    temp_token.word = ft_strdup(equal_sign + 1);
    temp_token.expand = true;
    expand_token(&temp_token, data);
    temp = ft_strjoin(new_cmd, temp_token.word);
    free(new_cmd);
    free(temp_token.word);
    new_cmd = ft_strjoin(temp, "\"");
    free(temp);
    temp == NULL;
    return(new_cmd);
}

static void add_or_change_envp(char *new_cmd, t_data *data)
{
    char *variable;
    char *equal;

    equal = ft_strchr(new_cmd, '=');
    if (equal == NULL)
        variable = new_cmd;
    else
        variable = ft_substr(new_cmd, 0, equal - new_cmd - 1);
    if (getenv(variable) != NULL)
        change_envp(data, new_cmd);
    else
        add_envp(data, new_cmd);
    free(variable);
}