#include "minishell.h"
#include <stdio.h>
#include "libft.h"
#include <stdbool.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "parse.h"

static void	initialize(t_data *data, char **environ);
static void	copy_envp(t_data *data, char **old_envp);
static int reader_loop(t_data *data);
static bool	check_syntax(char *input);


int	main(int argc, char **argv, char **environ)
{
	t_data *data;

	if (argc == 0 || argv == NULL) //
		return (2); //
	data = malloc(sizeof(t_data));
	initialize(data, environ);
	int	i = 0;
	while (data->envp[i]) //test
	{
		printf("%s\n", data->envp[i++]);
	}
	// set_signal(); // setting signal ctrl+D, ctrl+C, ctrl+/

	reader_loop(data); // 
	// exit_shell(); // free all and exit
	return (0);
}

static void	initialize(t_data *data, char **environ)
{
	copy_envp(data, environ);
	data->is_interactive = true;
	data->exit_status = 0;
}

static void	copy_envp(t_data *data, char **old_envp)
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
	data->envp = new_envp;
}

static int	reader_loop(t_data *data)
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
			parse_input(input, data); // parser
			// add_history(input); // do we use history?
			free(input);
			input = NULL;
		}
	}
	printf("reader_loop done");
	return (0);
}

static bool	check_syntax(char *input)
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
