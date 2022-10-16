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
#include <unistd.h>

void	builtin_env(char **cmd, t_data *data)
{
	if (cmd[1] != NULL)
	{
		print_error(cmd[0], "usage: pwd with no options or arguments", NULL);
		data->exit_status = 1;
	}
	else
	{
		print_envp(data, NULL);
		data->exit_status = 0;
	}
}
