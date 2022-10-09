#include "parse.h"

static void	expand_word(t_token *token, t_data *data);

void	expand_token(t_token_list *token_list, t_data *data)
{
	t_list	*temp;

	temp = token_list->head;
	while (temp != NULL)
	{
		if (((t_token *)temp->content)->expand == true)
			expand_word((t_token *)temp->content, data);
		temp = temp->next;
	}
}

static void	expand_word(t_token *token, t_data *data)
{
	expand_parameter(token, data);
	expand_quote(token);
}
