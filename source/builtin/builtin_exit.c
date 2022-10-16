/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:00:56 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:00:57 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

void	builtin_exit(char **cmd, t_data *data)
{
	if (cmd[1] == NULL)
		exit(data->exit_status);
	else if (cmd [2] != NULL)
	{
		print_error(cmd[0], "too many arguments", false);
		data->exit_status = 1;
		return ;
	}
	data->exit_status = ft_atoi(cmd[1]);
	exit(data->exit_status);
}
 