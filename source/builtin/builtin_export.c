/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:00:46 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:00:47 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include "parse.h"
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static void	print_export(t_data *data);
static void	add_or_change_envp(char *new_cmd, t_data *data);

void	builtin_export(char **cmd, t_data *data)
{
	int		i;
	char	*equal;

	g_exit_status = 0;
	if (cmd[1] == NULL)
		print_export(data);
	else
	{
		i = 1;
		g_exit_status = 0;
		while (cmd[i] != NULL)
		{
			equal = ft_strchr(cmd[i], '=');
			if (equal == cmd[i] || (cmd[i][0] >= '0' && cmd[i][0] <= '9'))
			{
				errno = 22;
				print_error(cmd[0], cmd[i], true);
				g_exit_status = 1;
			}
			else
				add_or_change_envp(cmd[i], data);
			i++;
		}
	}
}

static void	add_or_change_envp(char *new_cmd, t_data *data)
{
	char	*equal;
	int		i;

	i = 0;
	equal = ft_strchr(new_cmd, '=');
	if (equal != NULL)
	{
		while (data->envp[i] != NULL)
		{	
			if (ft_strncmp(new_cmd, data->envp[i], equal - new_cmd) == 0)
			{
				change_envp(data, new_cmd);
				return ;
			}
			i++;
		}
	}
	add_envp(data, new_cmd);
}

static void	print_export(t_data *data)
{
	char	*value;
	char	*variable;
	int		i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		value = ft_strchr(data->envp[i], '=');
		printf("declare -x ");
		if (value == NULL)
			printf("%s\n", data->envp[i]);
		else
		{
			variable = ft_substr(data->envp[i], 0, value - data->envp[i] + 1);
			printf("%s\"%s\"\n", variable, value + 1);
			free(variable);
		}
		i++;
	}

}