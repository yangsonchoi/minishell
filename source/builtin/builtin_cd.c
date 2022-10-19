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
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	cd_envp(t_data *data, char *old_cwd);

void	builtin_cd(char **cmd, t_data *data)
{
	char	*old_cwd;

	if (cmd [1] == NULL)
		print_error(cmd[0], "usage: cd [dir]", false);
	else
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(cmd[1]) == -1)
		{
			print_error(cmd[0], cmd[1], true);
			g_exit_status = 1;
		}
		else
			cd_envp(data, old_cwd);
		free(old_cwd);
	}
}

static void	cd_envp(t_data *data, char *old_cwd)
{
	char	*temp;
	char	*new_pwd;

	temp = ft_strjoin("OLDPWD=", old_cwd);
	change_envp(data, temp);
	free(temp);
	temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
	change_envp(data, new_pwd);
	free(new_pwd);
}