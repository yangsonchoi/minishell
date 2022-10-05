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