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
			return (1);
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
	enum e_type	type;
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
	token_list = break_input(input, token_list);



}

void	*break_input(char *input, t_token_list *token_list)
{
	t_list		*new_list;
	int			i;
	enum e_type	type;
	void *new_token;
	
	if (input == NULL)
		return ;
	while (input[i])
	{
		new_token = get_next_token(input[i]);
		new_list = 
		while (whitespace(input[i]) == true)
			i++;
		
	}
}