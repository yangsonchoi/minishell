/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:06:56 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:06:58 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

static int	expand_sign(t_token *token, int i, t_data *data);
static int	convert_variable(char **parameter, char *input);

void	expand_parameter(t_token *token, t_data *data)
{
	int		i;
	bool	d_quote;

	i = 0;
	d_quote = false;
	while ((token->word)[i] != 0)
	{
		if ((token->word)[i] == '\"')
		{
			d_quote = !d_quote;
			i++;
		}
		else if ((token->word)[i] == '\'' && d_quote == false)
			i += ft_strchr(&(token->word)[i + 1], '\'') - &(token->word)[i];
		else if ((token->word)[i] == '$')
			i += expand_sign(token, i, data);
		else
			i++;
	}
}

static int	expand_sign(t_token *token, int i, t_data *data)
{
	char	*input;
	char	*front_str;
	char	*parameter;
	char	*back_str;
	int		len;

	input = token->word;
	len = 0;
	front_str = ft_substr(input, 0, i);
	parameter = NULL;
	if (input[i + 1] == '?')
	{
		parameter = ft_itoa(data->exit_status);
		len++;
	}
	else
		len += convert_variable(&parameter, &input[i + 1]);
	back_str = ft_substr(input, i + 1 + len, ft_strlen(&input[i + 1 + len]));
	len = ft_strlen(parameter);
	join_string(token, front_str, parameter, back_str);
	return (len);
}

static int	convert_variable(char **parameter, char *input)
{
	int		len;
	char	*target;
	char	*temp;

	len = 0;
	while (input[len] != 0)
	{
		if (is_whitespace(input[len]) == true || input[len] == '\'' \
			|| input[len] == '\"' || input[len] == '$')
			break ;
		len++;
	}
	target = ft_substr(input, 0, len);
	temp = getenv(target);
	if (temp == NULL)
		temp = "";
	*parameter = ft_strdup(temp);
	free(target);
	return (len);
}

void	join_string(t_token *token, char *front, char *mid, char *back)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(front, mid);
	free(front);
	front = NULL;
	free(mid);
	mid = NULL;
	result = ft_strjoin(temp, back);
	free(temp);
	temp = NULL;
	free(back);
	back = NULL;
	free(token->word);
	token->word = NULL;
	token->word = result;
}
