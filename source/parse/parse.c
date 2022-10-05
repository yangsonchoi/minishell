#include "parse.h"
#include <stdlib.h>

#include <stdio.h> // printf

void	parse_input(char *input)
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
		printf("word : %s, type : %d\n", ((t_token *)temp->content)->word, ((t_token *)temp->content)->type);
		temp = temp->next;
	}
	// expand_token(token_list); expand
	// execute_pipe();
	free_list(token_list);
	free(token_list);
}