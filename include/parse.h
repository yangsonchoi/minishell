#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "stdbool.h"

enum e_type
{
	WORD,
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

/*
** parse.c
*/
void	parse_input(char *input);

/*
** parse_token.c
*/
void	break_input(char *input, t_token_list *token_list);
bool	is_whitespace(char input);

/*
** parse_expand.c
*/
void	expand_token(t_token_list *token_list);

/*
** parse_parameter.c
*/
void	expand_parameter(t_token *token);
void	join_string(t_token *token, char *front, char *mid, char *back);

/*
** parse_quote.c
*/
void	expand_quote(t_token *token);

/*
** parse_free.c
*/
void	free_list(t_token_list *token_list);

#endif