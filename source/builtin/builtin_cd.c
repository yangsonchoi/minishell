/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:02:16 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:02:17 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

void	builtin_cd(char **cmd, t_data *data)
{
	char	*old_cwd;
	char	*temp;

	if (cmd [1] == NULL)
		print_error(cmd[0], "usage: cd [dir]", false);
	else
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(cmd[1]) == -1)
		{
			print_error(cmd[0], cmd[1], true);
			data->exit_status = 1;
		}
		else
		{
			temp = getcwd(NULL, 0);
			change_envp(data, "OLDPWD", old_cwd);
			change_envp(data, "PWD", temp);
			free(temp);
			data->exit_status = 0;
		}
		free(old_cwd);
	}
}
