/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_add_change.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:45:58 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 14:45:59 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	add_envp(t_data *data, char *new_cmd)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (data->envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (new_envp == NULL)
	{
		err_sys("export: malloc failed", NULL);
		return ;
	}
	i = 0;
	while (data->envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		free(data->envp[i++]);
	}
	new_envp[i++] = ft_strdup(new_cmd);
	new_envp[i] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

void	change_envp(t_data *data, char *new_cmd)
{
	int		i;
	char	*equal;

	i = 0;
	equal = ft_strchr(new_cmd, '=');
	if (equal == NULL)
		return ;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(new_cmd, data->envp[i], equal - new_cmd) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(new_cmd);
		}
		i++;
	}
}
