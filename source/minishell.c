#include "minishell.h"
#include <stdio.h>
#include "libft.h"
#include <stdbool.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "parse.h"

void	copy_envp(char **old_envp);
static int reader_loop(void);
bool	check_syntax(char *input);


int	main(int argc, char **argv)
{
	int i = 0;
	
	if (argc == 0 || argv == NULL) //
		return (2); //
	copy_envp(environ);
	while (environ[i]) //test
	{
		printf("%s\n", environ[i++]);
	}
	// set_signal(); // setting signal ctrl+D, ctrl+C, ctrl+/

	reader_loop(); // 
	// exit_shell(); // free all and exit
	return (0);
}

void	copy_envp(char **old_envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (old_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (new_envp == NULL)
		exit(1);
	i = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	old_envp = new_envp;
}

static int	reader_loop(void)
{
	char	*input;
	
	while (true)
	{
		input = readline("minishell$ ");
		if (input == NULL || check_syntax(input) == false)
		{
			printf("syntax error");
			free(input);
		}
		else
		{
			parse_input(input); // parser
			// add_history(input); // do we use history?
			free(input);
			input = NULL;
		}
	}
	printf("reader_loop done");
	return (0);
}

bool	check_syntax(char *input)
{
	while (*input != 0)
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
		input++;
	}
	return (true);
}



