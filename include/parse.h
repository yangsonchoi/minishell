#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "stdbool.h"

enum e_type
{
	WORD,
	QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	HERE_DOC,
	APPEND,
};

typedef struct			s_token
{
	char				*word;
	enum e_type			type;
	bool				expand;
} 						t_token;

typedef struct			s_token_list
{
	int		token_count;
	bool	pipe;
	t_list	*head;
}						t_token_list;

void	parse_input(char *input);
void	break_input(char *input, t_token_list *token_list);
void	expand_token(t_token_list *token_list);
void	free_list(t_token_list *token_list);

#endif