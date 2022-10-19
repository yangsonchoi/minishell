/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:00:31 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/19 19:00:33 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"
#include "utils.h"
#include <stdlib.h>

static bool	check_pipe(t_token_list *token_list);
static bool	check_redirection(t_cmd **cmd_list);
static void	exe_pipe_or_shell(t_cmd **cmd_list, int pipe_count, t_data *data);
static void	free_cmd_list(t_cmd **list);

void	execute_line(t_token_list *token_list, t_data *data)
{
	t_cmd	**cmd_list;

	if (check_pipe(token_list) == false)
	{	
		print_error("syntax error near unexpected token \'|\'", NULL, false);
		g_exit_status = 2;
	}
	else
	{
		if (token_list->head != NULL)
		{
			cmd_list = malloc(sizeof(t_cmd *) * (token_list->pipe_count + 2));
			if (cmd_list == NULL)
				print_error("malloc failed", NULL, false);
			token_to_command(token_list, cmd_list);
			if (check_redirection(cmd_list) == true)
				exe_pipe_or_shell(cmd_list, token_list->pipe_count, data);
			else
			{	
				print_error("syntax error", "redirection", false);
				g_exit_status = 2;
			}
			free_cmd_list(cmd_list);
		}
	}
}

static void	exe_pipe_or_shell(t_cmd **cmd_list, int pipe_count, t_data *data)
{
	if (pipe_count > 0)
		execute_pipe(pipe_count + 1, cmd_list, data);
	else
		execute_subshell(cmd_list[0], data);
}

static bool	check_pipe(t_token_list *token_list)
{
	t_list	*temp;
	t_token	*check;

	temp = token_list->head;
	if (((t_token *)temp->content)->type == PIPE)
		return (false);
	while (temp != NULL && temp->next != NULL)
	{
		if (((t_token *)temp->content)->type == PIPE)
		{
			if (temp->next != NULL)
			{
				check = (t_token *)(temp->next->content);
				if (check != NULL && check->type == PIPE)
					return (false);
			}
		}
		temp = temp->next;
	}
	if (((t_token *)temp->content)->type == PIPE)
		return (false);
	return (true);
}

static bool	check_redirection(t_cmd **cmd_list)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_list[i] != NULL)
	{
		j = -1;
		while (cmd_list[i]->redirect[++j])
		{
			if (j % 2 == 0)
			{
				if (cmd_list[i]->redirect[j]->type == WORD)
					return (false);
			}
			else if (j % 2 == 1)
			{
				if (cmd_list[i]->redirect[j]->type != WORD)
					return (false);
			}
		}
		if (j % 2 != 0)
			return (false);
		i++;
	}
	return (true);
}

static void	free_cmd_list(t_cmd **list)
{
	int	i;
	int	j;

	i = 0;
	while (list[i] != NULL)
	{
		j = 0;
		while (list[i]->cmd[j] != NULL)
		{
			free(list[i]->cmd[j]);
			j++;
		}
		free(list[i]->cmd);
		free(list[i]->redirect);
		free(list[i]);
		i++;
	}
	free(list);
}
