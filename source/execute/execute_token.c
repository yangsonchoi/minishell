/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:39:18 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 16:39:19 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"
#include <stdlib.h>
#include "libft.h"
#include "utils.h"

#include <stdio.h>//test

static void	get_next_pipe(t_token_list *token_list, \
							t_cmd *new_cmd, int pipe_num);
static void	get_next_cmd(t_list *start, t_cmd *new_cmd);
static void	copy_cmd_redirect(t_list *start, t_cmd *new_cmd);

void	token_to_command(t_token_list *token_list, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	while (i < token_list->pipe_count + 1)
	{
		printf("here11\n");
		new_cmd = malloc(sizeof(t_cmd));
		if (new_cmd == NULL)
		{
			print_error("malloc failed", NULL, true);
			return ;
		}
		get_next_pipe(token_list, new_cmd, i);
		cmd_list[i] = new_cmd;
		i++;
	}
	cmd_list[i] = NULL;
}

static void	get_next_pipe(t_token_list *token_list, \
							t_cmd *new_cmd, int shell_num)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = token_list->head;
	while (i < shell_num)
	{
		if (((t_token *)temp->content)->type == PIPE)
			i++;
		temp = temp->next;
	}
	get_next_cmd(temp, new_cmd);
}

static void	get_next_cmd(t_list *start, t_cmd *new_cmd)
{	
	int		word_cnt;
	int		red_cnt;
	t_list	*temp;

	temp = start;
	word_cnt = 0;
	red_cnt = 0;
	while (temp != NULL && ((t_token *)temp->content)->type != PIPE)
	{
		if (((t_token *)temp->content)->type == WORD)
			word_cnt++;
		else
		{
			red_cnt++;
			temp = temp->next;
		}
		if (temp != NULL)
			temp = temp->next;
	}
	new_cmd->cmd = malloc(sizeof(char *) * (word_cnt + 1));
	new_cmd->redirect = malloc(sizeof(t_token *) * ((red_cnt * 2) + 1));
	if (new_cmd->cmd == NULL || new_cmd->redirect == NULL)
		print_error("malloc failed", NULL, true);
	copy_cmd_redirect(start, new_cmd);
}

static void	copy_cmd_redirect(t_list *cmd, t_cmd *new_cmd)
{
	int		w_cnt;
	int		red_cnt;
	int		i;

	w_cnt = 0;
	red_cnt = 0;
	while (cmd != NULL && ((t_token *)cmd->content)->type != PIPE)
	{
		if (((t_token *)cmd->content)->type == WORD)
			new_cmd->cmd[w_cnt++] = ft_strdup(((t_token *)cmd->content)->word);
		else
		{
			i = 0;
			while (cmd != NULL && i < 2)
			{
				new_cmd->redirect[red_cnt] = cmd->content;
				if (i++ == 0)
					cmd = cmd->next;
			}
		}
		if (cmd != NULL)
			cmd = cmd->next;
	}
	new_cmd->cmd[w_cnt] = NULL;
	new_cmd->redirect[red_cnt] = NULL;
}
