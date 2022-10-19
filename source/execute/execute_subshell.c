/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:40:53 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/19 21:21:32 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include "builtin.h"
#include "utils.h"
#include <fcntl.h>

static bool	check_builtin(char *cmd, enum e_builtin_type *type);
static void	default_redirection(t_data *data);

void	execute_subshell(t_cmd *cmd_list, t_data *data)
{
	enum e_builtin_type	builtin_type;

	if (cmd_list->redirect != NULL)
		perform_redirection(cmd_list->redirect);
	if (cmd_list->cmd[0] != NULL)
	{
		if (check_builtin(cmd_list->cmd[0], &builtin_type) == true)
			execute_builtin(cmd_list->cmd, data, builtin_type);
		else
			execute_cmd(cmd_list->cmd, data);
	}
	if (data->is_interactive == false)
		exit(g_exit_status);
	else if (cmd_list->redirect != NULL)
		default_redirection(data);
}

static bool	check_builtin(char *cmd, enum e_builtin_type *type)
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

static void	default_redirection(t_data *data)
{
	if (data->std_fd[0] != STDIN_FILENO)
	{
		if (dup2(data->std_fd[0], STDIN_FILENO) != STDIN_FILENO)
			print_error("dup2 error", NULL, true);
	}
	if (data->std_fd[1] != STDOUT_FILENO)
	{
		if (dup2(data->std_fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			print_error("dup2 error", NULL, true);
	}
	if (data->std_fd[2] != STDERR_FILENO)
	{
		if (dup2(data->std_fd[2], STDERR_FILENO) != STDERR_FILENO)
			print_error("dup2 error", NULL, true);
	}
}
