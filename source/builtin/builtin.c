/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:02:27 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:02:29 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

void	execute_builtin(char **cmd, t_data *data, enum e_builtin_type type)
{
	if (type == ECHO)
		builtin_echo(cmd);
	else if (type == CD)
		builtin_cd(cmd, data);
	else if (type == PWD)
		builtin_pwd(cmd);
	else if (type == EXPORT)
		builtin_export(cmd, data);
	else if (type == UNSET)
		builtin_unset(cmd, data);
	else if (type == ENV)
		builtin_env(cmd, data);
	else if (type == EXIT)
		builtin_exit(cmd);
}
