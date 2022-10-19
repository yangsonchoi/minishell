/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:01:04 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:01:05 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

void	builtin_env(char **cmd, t_data *data)
{
	int	i;

	if (cmd[1] != NULL)
	{
		print_error(cmd[0], "usage: pwd with no options or arguments", NULL);
		g_exit_status = 1;
	}
	else
	{
		i = 0;
		while (data->envp[i] != NULL)
		{
			if (ft_strchr(data->envp[i], '=') != NULL)
				printf("%s\n", data->envp[i]);
			g_exit_status = 0;
			i++;
		}
	}
}
