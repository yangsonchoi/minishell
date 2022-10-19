#include "minishell.h"
#include "libft.h"
#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	initialize(t_data *data, char **environ);
static void	reader_loop(t_data *data);
static bool	check_syntax(char *input);
static void	copy_envp(t_data *data, char **old_envp);

int	main(int argc, char **argv, char **environ)
{
	t_data data;

	(void)argc;
	(void)argv;
	initialize(&data, environ);
	int	i = 0;
	while (data.envp[i]) //test
	{
		printf("%s\n", data.envp[i++]);
	}
	set_signal(); // setting signal ctrl+D, ctrl+C, ctrl+/

	reader_loop(&data); // 
	// exit_shell(); // free all and exit
	return (0);
}

static void	initialize(t_data *data, char **environ)
{
	copy_envp(data, environ);
	data->is_interactive = true;
	g_exit_status = 0;
}

static void	reader_loop(t_data *data)
{
	char	*input;
	
	while (true)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (input == NULL || check_syntax(input) == false)
		{
			printf("%s, syntax error\n", input); // writwe 2
			free(input);
		}
		else
		{
			parse_input(input, data); // parser
			// add_history(input); // do we use history?
			free(input);
			input = NULL;
		}
		system("leaks minishell");
	}
	printf("reader_loop done"); // test
}

static bool	check_syntax(char *input)
{
	while (*input != 0)
	{
		if (*input == '\"')
		{
			input = ft_strchr(input + 1, '\"');
			if (input == NULL)
				return (false);
		}
		else if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (false);
		}
		else if (*input == '\\' || *input == ';')
			return (false);
		else if (*input == '$' && (is_whitespace(*(input + 1)) == true \
				|| *(input + 1) == '$' || *(input + 1) == '|' || *(input + 1) == '<' \
				|| *(input + 1) == '>' || *(input + 1) == '\0'))
			return (false);
		input++;
	}
	return (true);
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
	{
		print_error(NULL, "malloc failed", false);
		return ;
	}
	i = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	old_envp = new_envp;
	data->envp = old_envp;
}