/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_remove_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:38:42 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 14:38:44 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*get_target_address(char **envp, char *target);

void	remove_envp(t_data *data, char *target)
{
	int		i;
	char	**new_envp;
	char	*remove_envp;

	remove_envp = get_target_address(data->envp, target);
	if (remove_envp == NULL)
		return ;
	i = 0;
	while (data->envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (data->envp[i] == NULL)
	{
		if (data->envp[i] != remove_envp)
			new_envp[i] = data->envp[i];
		i++;
	}
	free(remove_envp);
	free(data->envp);
	data->envp = new_envp;
}

static char	*get_target_address(char **envp, char *target)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(target);
	temp = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(target, envp[i], len) && envp[i][len] == '=')
		{
			temp = envp[i];
			break ;
		}
		i++;
	}
	return (temp);
}

void	print_envp(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (data->envp[i] != NULL)
		{
			printf("%s", str);
			printf("%s\n", data->envp[i]);
			i++;
		}
	}
	else
	{
		while (data->envp[i] != NULL)
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
	}
}
