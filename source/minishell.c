#include <stdio.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include <stdbool.h>

int	main(int argc, char **argv, char **envp)
{
	char	**mini_envp;

	mini_envp = copy_envp(envp);
	set_signal(); // setting signal ctrl+D, ctrl+C, ctrl+/

	reader_loop(); // 
	exit_shell(); // free all and exit
}

char	**copy_envp(char **old_envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (old_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static void	reader_loop(arg)
{
	char	*input;
	
	while (true)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			return (1); // exit? readline fail
		else if(check_syntax(input) == false)
			return (1); // exit? unclosed quate, / ; 
		else
		{
			parse(input); // parser
			add_history(input); // do we use history?
			free(input);
			input = NULL;
		}
	}
	return (0);
}

bool	check_syntax(char *input)
{
	while (*input == '\0')
	{
		if (*input == '\"')
			input = ft_strchr(input + 1, '\"');
		if (input == NULL)
			return (false);
		if (*input == '\'')
			input = ft_strchr(input + 1, '\'');
		if (input == NULL)
			return (false);
		if (*input == '\\' || *input == ';')
			return (false);
		++input;
	}
	return (true);
}



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



static void parse_input(char *input)
{
	t_token_list	*token_list;
	
	token_list = malloc(sizeof(t_token_list));
	if (token_list == NULL)
		return ;
	break_input(input, &token_list);


}

void	*break_input(char *input, t_token_list *token_list)
{
	int			i;
	enum e_type	type;
	void *new_token;
	
	if (input == NULL)
		return ;
	while (input[i])
	{
		new_token = get_next_token(&input[i], token_list);
		new_list = 123;
		while (whitespace(input[i]) == true)
			i++;
		
	}
}

int	get_next_token(char *input, t_token_list *token_list)
{
	t_token	*new_token;
	int len;
	char *new_word;

	len = 0;
	new_token = malloc(sizeof(new_token));
	if (new_token == NULL)
		exit(MALLOC);
	len = get_word(input, new_token)

	return (len);
}

int	get_word(char *input, t_token *new_token)
{
	int len;

	len = 0;
	while (input[len])
	{
		if (input[len] == '|' || input[len] == '<' || input[len] == '>' || whitespace)
			break;
		else if (*input == '\'' || *input == '\"' || *input == '$')
		{
			if (*input == '\'')
				len += ft_strchr(&input[len + 1], '\'') - &input[len];
			else if (*input == '\"')
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

int	get_type(char *input, t_token *new_token)
{
	int	len;

	len = 1;
	if (input[len] == '<')
	{	
		new_token->type = REDIRECTION_INPUT;
		if (input[len + 1] == '<')
		{
			new_token->type = HERE_DOC;
			len = 2;
		}
	}
	else if (input[len] == '>')
	{
		new_token->type = REDIRECTION_OUTPUT;
		if (input[len + 1] == '>')
		{
			new_token->type = APPEND;
			len = 2;
		}
	}
	else
		new_token->type = PIPE;
	return (len);
}