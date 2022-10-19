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
#include "execute.h"
#include <stdlib.h>

void	parse_input(char *input, t_data *data)
{
	t_token_list	token_list;

	token_list.head = NULL;
	token_list.pipe_count = 0;
	token_list.token_count = 0;
	break_input(input, &token_list);
	expand_token_list(&token_list, data);
	if (token_list.head != NULL)
		execute_line(&token_list, data);
	free_list(&token_list);
}
