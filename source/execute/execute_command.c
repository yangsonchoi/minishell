/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:40:53 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 16:40:55 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include "builtin.h"
#include "stdio.h"// for test
static bool	check_builtin(char *cmd, enum e_builtin_type *type);

void	execute_subshell(t_cmd *cmd_list, t_data *data)
{
	enum e_builtin_type	builtin_type;

	// if (cmd_list->redirect != NULL)
	//	(perform_redirection(*cmd_list), data);
	if (check_builtin(cmd_list->cmd[0], &builtin_type) == true)
		execute_builtin(cmd_list->cmd, data, builtin_type);
	// else
	//	execute_program(); // 
	// if(data->is_interactive == true)
	//	 (default_redierction());
	// else 
	//  exit(data->exit_status);
}

static bool check_builtin(char *cmd, enum e_builtin_type *type)
{
	bool	result;

	result = true;
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		*type = ECHO;
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		*type = CD;
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		*type = PWD;
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		*type = EXPORT;
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		*type = UNSET;
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		*type = ENV;
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		*type = EXIT;
	else
		result = false;
	return (result);
}
