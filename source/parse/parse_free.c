/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:07:07 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:07:09 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include "libft.h"

static void	free_token(void *content);

void	free_list(t_token_list *token_list)
{
	ft_lstclear(&(token_list->head), &free_token);
	token_list->head = NULL;
}

static void	free_token(void *content)
{
	free(((t_token *)content)->word);
	free((t_token *)content);
}
