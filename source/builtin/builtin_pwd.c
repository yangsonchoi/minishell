/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:49:30 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 14:49:32 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void	builtin_pwd(char **cmd)
{
	char	*pwd;

	if (cmd[1] != NULL)
	{
		print_error(cmd[0], "usage: pwd with no option or argument", false);
		g_exit_status = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		g_exit_status = 0;
	}
}
