#include "parse.h"

void	expand_token(t_token_list *token_list)
{
	t_list	*temp;

	temp = token_list->head;
	while (temp != NULL)
	{
		if (((t_token *)temp->content)->expand == true)
			expand_word((t_token *)temp->content);
		temp = temp->next;
	}
}

void	expand_word(t_token *token)
{
		
}

char	*expand_parameter(t_token *token)
{
	char	*temp_word;
	int		i;
	bool	quote;
	bool	d_quote;

	i = 0;
	quote = false;
	d_quote = false;
	temp_word = token->word;
	while(raw_word[i] != 0)
	{
		if (raw_word[i] == '\"')
			d_quote = !d_quote;
		else if (raw_word[i] == '\'' && d_quote == false)
			i += ft_strchr(&raw_word[i + 1], '\'') - &raw_word[i];
		else if ()
	}
}