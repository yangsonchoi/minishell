#include "parse.h"
#include "minishell.h"
#include <stdlib.h>
#include "execute.h"

#include <stdio.h> // printf

void	parse_input(char *input, t_data *data)
{
	t_token_list	*token_list;
	
	token_list = malloc(sizeof(t_token_list));
	if (token_list == NULL)
		return ;
	token_list->head = NULL;
	break_input(input, token_list);
	t_list	*temp; // test
	temp = token_list->head;
	while (temp != NULL) 
	{
		printf("word : %s, type : %d, expand : %d\n", ((t_token *)temp->content)->word, ((t_token *)temp->content)->type, ((t_token *)temp->content)->expand);
		temp = temp->next;
	}
	expand_token(token_list, data);
	temp = token_list->head;
	while (temp != NULL) 
	{
		printf("word : %s\n", ((t_token *)temp->content)->word);
		temp = temp->next;
	}
	execute_line(token_list, data);
	free_list(token_list);
	free(token_list);
}
