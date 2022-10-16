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

static void	add_or_change_envp(char *new_cmd, t_data *data);

void	builtin_export(char **cmd, t_data *data)
{
	int		i;
	char	*equal;

	if (cmd[1] == NULL)
		print_envp(data, "declare -x");
	else
	{
		i = 1;
		data->exit_status = 0;
		while (cmd[i] != NULL)
		{
			equal = ft_strchr(cmd[i], '=');
			if (equal == cmd[i])
			{
				errno = 22;
				print_error(cmd[0], cmd[i], true);
				data->exit_status = 1;
			}
			else
				add_or_change_envp(cmd[i], data);
		}
		i++;
	}
}

static void	add_or_change_envp(char *new_cmd, t_data *data)
{
	char	*variable;
	char	*value;
	int		i;

	i = 0;
	value = ft_strchr(new_cmd, '=');
	if (value == NULL)
		variable = new_cmd;
	else
	{
		variable = ft_substr(new_cmd, 0, value - new_cmd - 1);
		value = value + 1;
	}
	while (data->envp[i] != NULL)
	{	
		if (ft_strncmp(variable, data->envp[i], ft_strlen(variable)) == 0)
		{
			change_envp(data, variable, value);
			free(variable);
			return ;
		}
		i++;
	}
	add_envp(data, variable, value);
	free(variable);
}
