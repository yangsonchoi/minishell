#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

void    builtin_cd(char **cmd, t_data *data)
{
    char *old_cwd;
    char *temp;

    if (cmd [1] == NULL)
        print_error(cmd[0], "usage: cd [dir]", false);
    else
    {
        temp = getcwd(NULL, 0);
        if(chdir(cmd[1]) == -1)
        {
            print_error(cmd[0], cmd[1], true);
            data->exit_status = 1;
        }
        else
        {
            old_cwd = 
            change_envp("OLDPWD", old_cwd);
            change_envp("PWD", getcwd(NULL, 0));
            data->exit_status = 1;
        }
    }
}