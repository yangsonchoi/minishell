/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:49:13 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 14:49:16 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>

void	builtin_unset(char **cmd, t_data *data)
{
	data->exit_status = 0;
	if (ft_strchr(cmd[1], '=') != NULL)
	{
		data->exit_status = 1;
		errno = 22;
		print_error(cmd[0], cmd[1], true);
		return ;
	}
	if (getenv(cmd[1]) != NULL)
		remove_envp(data, cmd[1]);
}