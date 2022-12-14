/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:07:16 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:07:18 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	expand_token_list(t_token_list *token_list, t_data *data)
{
	t_list	*temp;

	temp = token_list->head;
	while (temp != NULL)
	{
		if (((t_token *)temp->content)->expand == true)
			expand_token((t_token *)temp->content, data);
		temp = temp->next;
	}
}

void	expand_token(t_token *token, t_data *data)
{
	expand_parameter(token, data);
	expand_quote(token);
}
