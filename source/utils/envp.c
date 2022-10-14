#include "utils.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	copy_envp(t_data *data, char **old_envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (old_envp[i] != NULL)
        i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (new_envp == NULL)
    {
		print_error(NULL, "malloc failed", false);
        return ;
    }
    i = 0;
	while (old_envp[i] != NULL)
	{
        new_envp[i] = ft_strdup(old_envp[i]);
        i++;
    }
	new_envp[i] = NULL;
	data->envp = new_envp;
}

void	add_envp(t_data *data, char *add_envp)
{
	char	**new_envp;
	int		i;

    if (add_envp == NULL)
        return ;
	i = 0;
	while (data->envp[i] != NULL)
        i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (new_envp == NULL)
    {
		print_error(NULL, NULL, true);
        return ;
    }
    i = 0;
	while (data->envp[i] != NULL)
	{
        new_envp[i] = ft_strdup(data->envp[i]);
        free(data->envp[i++]);
    }
    new_envp[++i] = ft_strdup(add_envp);
	new_envp[i] = NULL;
    free(data->envp);
	data->envp = new_envp;
}

void    remove_envp(t_data *data, char *target)
{
    int     i;
    char    **new_envp;
    char    *remove_envp;
    
    remove_envp = get_target_address(data->envp, target);
    if (remove_envp == NULL)
        return ;
    i = 0;
    while (data->envp[i] != NULL)
        i++;
    new_envp = malloc(sizeof(char *) * i);
    i = 0;
    while (data->envp[i] == NULL)
    {
        if (data->envp[i] != remove_envp)
            new_envp[i] = data->envp[i];
        i++;
    }
    free(remove_envp);
    free(data->envp);
    data->envp = new_envp;
}

static char *get_target_address(char **envp, char *target)
{
    char    *temp;
    int     len;
    int     i;

    i = 0;
    len = ft_strlen(target);
    temp = NULL;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(target, envp[i], len) && envp[i][len] == '=')
        {
            temp = envp[i];
            break ;
        }
        i++;
    }
    return (temp);
}

void    print_envp(t_data *data, char *str)
{
    int i;

    if (str != NULL)
    {
        while (data->envp[i] == NULL)
        {
            printf("%s", str);
            printf("%s\n", data->envp[i]);
            i++;
        }
    }
    else
    {
        while (data->envp[i] == NULL)
        {
            printf("%s\n", data->envp[i]);
            i++;
        }
    }
}