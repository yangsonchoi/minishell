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
#include <errno.h>

static bool	is_numeric(char *cmd);

void	builtin_exit(char **cmd)
{
	if (cmd[1] == NULL)
		exit(g_exit_status);
	else if (cmd [2] != NULL)
	{
		print_error(cmd[0], "too many arguments", false);
		g_exit_status = 1;
		return ;
	}
	if (is_numeric(cmd[1]) == false)
	{
		errno = 22;
		print_error(cmd[0], cmd[1], true);
		g_exit_status = 255;
		exit(g_exit_status);
	}
	g_exit_status = ft_atoi(cmd[1]);
	g_exit_status %= 256;
	if (g_exit_status < 0)
		g_exit_status += 256;
	exit(g_exit_status);
}

static bool	is_numeric(char *cmd)
{
	int						i;
	int						sign;
	unsigned long long		num;

	if (cmd[0] != '-' && cmd [0] != '+' && ft_isdigit(cmd[0]) == 0)
		return (false);
	i = 1;
	while (cmd[i] != '\0')
		if (ft_isdigit(cmd[i++]) == 0)
			return (false);
	i = 0;
	sign = 1;
	if (cmd[i] == '-' || cmd[i] == '+')
		if (cmd[i++] == '-')
			sign *= -1;
	num = 0;
	while (cmd[i] >= '0' && cmd[i] <= '9')
		num = num * 10 + (cmd[i++] - '0');
	if ((num > 9223372036854775807 && sign == 1) \
		|| (num > 9223372036854775808ULL && sign == -1))
		return (false);
	return (true);
}
