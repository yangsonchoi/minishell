#include "parse.h"
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

static int	get_token(char *input, t_token_list *token_list);
static int	get_word(char *input, t_token *new_token);
static int	get_type(char *input, t_token *new_token);

void	break_input(char *input, t_token_list *token_list)
{
	int			i;
	
	if (input == NULL)
		return ;
	i = 0;
	while (input[i] != 0 && is_whitespace(input[i]) == true)
		i++;
	while (input[i] != 0)
	{
		i += get_token(&input[i], token_list);
		while (input[i] != 0 && is_whitespace(input[i]) == true)
			i++;
	}
}

static int	get_token(char *input, t_token_list *token_list)
{
	t_list	*new_list;
	t_token	*new_token;
	int		len;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (0);
	len = 0;
	new_token->type = WORD;
	len = get_word(input, new_token);
	if (new_token->type == PIPE)
		token_list->pipe_count++;
	new_list = ft_lstnew((void *)new_token);
	ft_lstadd_back(&(token_list->head), new_list);
	return (len);
}

static int	get_word(char *input, t_token *new_token)
{
	int len;

	len = 0;
	while (input[len] != 0)
	{
		if (input[len] == '|' || input[len] == '<' || input[len] == '>' || is_whitespace(input[len]) == true)
			break;
		else if (input[len] == '\'' || input[len] == '\"' || input[len] == '$')
		{
			if (input[len] == '\'')
				len += ft_strchr(&input[len + 1], '\'') - &input[len];
			else if (input[len] == '\"')
				len += ft_strchr(&input[len + 1], '\"') - &input[len];
			new_token->expand = true;
		}
		len++;
	}
	if (len == 0)
		len = get_type(input, new_token);
	new_token->word = ft_substr(input, 0, len);
	return (len);
}

static int	get_type(char *input, t_token *new_token)
{
	int	len;

	len = 1;
	if (input[0] == '<')
	{
		new_token->type = REDIRECTION_INPUT;
		if (input[1] == '<')
		{
			new_token->type = HERE_DOC;
			len = 2;
		}
	}
	else if (input[0] == '>')
	{
		new_token->type = REDIRECTION_OUTPUT;
		if (input[1] == '>')
		{
			new_token->type = APPEND;
			len = 2;
		}
	}
	else
		new_token->type = PIPE;
	return (len);
}

bool	is_whitespace(char input)
{
	if (input == ' ' || (input <= 13 && input >= 9))
		return (true);
	else
		return (false);
}
