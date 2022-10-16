#include "execute.h"
#include "parse.h"
#include "utils.h"
#include <stdlib.h>

#include <stdio.h> // test

static bool	check_pipe(t_token_list *token_list);
static void	free_cmd_list(t_cmd **list);

void	execute_line(t_token_list *token_list, t_data *data)
{
	t_cmd	**cmd_list;

	if (check_pipe(token_list) == false)
		printf("minishell: syntax error near unexpected token \'|\'\n");
	else
	{
		cmd_list = malloc(sizeof(t_cmd *) * (token_list->pipe_count + 2));
		if (cmd_list == NULL)
			print_error("malloc failed", NULL, false);
		printf("pipe count : %d\n", token_list->pipe_count);
		token_to_command(token_list, cmd_list);
		printf("here22\n");
		int	i = 0;
		int	j = 0;
		while (cmd_list[i] != NULL)
		{
			j = 0;
			while (cmd_list[i]->cmd[j] != NULL)
			{
				printf("subshell : %d, cmd : %d, word : %s\n", i, j, cmd_list[i]->cmd[j]);
				j++;
			}
			j = 0;
			while (cmd_list[i]->redirect[j] != NULL)
			{
				printf("subshell : %d, type : %d, word : %s\n", i, cmd_list[i]->redirect[j]->type, cmd_list[i]->redirect[j]->word);
				j++;
			}
			i++;
		}
		// if (token_list->pipe_count > 0)
		// 	execute_pipe(cmd_list, token_list->pipe_count);
		// while (cmd_list != NULL)
	cmd_list[0]->pipe_fd[0, 1]

		execute_subshell(cmd_list[0], data);
		free_cmd_list(cmd_list);
	}
}

static bool	check_pipe(t_token_list *token_list)
{
	t_list	*temp;
	t_token	*check;

	temp = token_list->head;
	while (temp != NULL)
	{
		if (((t_token *)temp->content)->type == PIPE)
		{
			check = (t_token *)(temp->next->content);
			if (check != NULL && check->type == PIPE)
				return (false);
		}
		temp = temp->next;
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