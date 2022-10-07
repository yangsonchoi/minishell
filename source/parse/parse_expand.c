#include "parse.h"
#include <stdio.h> //

static void	expand_word(t_token *token);

void	expand_token(t_token_list *token_list)
{
	t_list	*temp;

	temp = token_list->head;
	while (temp != NULL)
	{
		if (((t_token *)temp->content)->expand == true)
			expand_word((t_token *)temp->content);
		printf("word : %s\n", ((t_token *)temp->content)->word); //
		temp = temp->next;
	}
}

static void	expand_word(t_token *token)
{
	expand_parameter(token);
	expand_quote(token);
}