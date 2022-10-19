/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:08:42 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:08:44 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"
#include <stdlib.h>
#include "execute.h"

#include <stdio.h> // printf

void	parse_input(char *input, t_data *data)
{
	t_token_list	token_list;

	token_list.head = NULL;
	token_list.pipe_count = 0;
	token_list.token_count = 0;
	break_input(input, &token_list);
	t_list	*temp;// test
	temp = token_list.head;
	while (temp != NULL)
	{
		printf("word : %s, type : %d, expand : %d\n", ((t_token *)temp->content)->word, ((t_token *)temp->content)->type, ((t_token *)temp->content)->expand);
		temp = temp->next;
	}
	expand_token_list(&token_list, data);
	temp = token_list.head;
	while (temp != NULL)
	{
		printf("word : %s\n", ((t_token *)temp->content)->word);
		temp = temp->next;
	}
	if (token_list.head != NULL)
		execute_line(&token_list, data);
	free_list(&token_list);
}
