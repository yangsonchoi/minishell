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

static char	*strjoin_var_val(char *variable, char *value);

void	add_envp(t_data *data, char *variable, char *value)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (data->envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (new_envp == NULL)
	{
		print_error("export", "malloc_failed", true);
		return ;
	}
	i = 0;
	while (data->envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		free(data->envp[i++]);
	}
	new_envp[i++] = strjoin_var_val(variable, value);
	new_envp[i] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

void	change_envp(t_data *data, char *variable, char *value)
{
	int		i;
	char	*temp;

	i = 0;
	if (value == NULL)
		temp = ft_strdup(variable);
	else
		temp = strjoin_var_val(variable, value);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(variable, data->envp[i], ft_strlen(variable)) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = temp;
		}
		i++;
	}
}

static char	*strjoin_var_val(char *variable, char *value)
{
	char	*temp_1;
	char	*temp_2;

	if (value == NULL)
	{
		temp_1 = ft_strdup(variable);
	}
	else
	{
		temp_1 = ft_strjoin(variable, "=\"");
		temp_2 = ft_strjoin(temp_1, value);
		free(temp_1);
		temp_1 = ft_strjoin(temp_2, "\"");
		free(temp_2);
		temp_2 = NULL;
	}
	return (temp_1);
}
