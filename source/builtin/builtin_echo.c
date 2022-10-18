/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:01:23 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:01:25 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	builtin_echo(char **cmd, t_data *data)
{
	int	i;
	
	data->exit_status = 0;
	if (cmd[1] == NULL)
	{	
		printf("\n");
		return ;
	}
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
		i = 2;
	else
		i = 1;
	while (cmd[i] != NULL && cmd[i + 1] != NULL)
	{
		printf("%s ", cmd[i]);
		i++;
	}
	if (cmd[i] != NULL)
		printf("%s", cmd[i]);
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) != 0)
		printf("\n");
}
