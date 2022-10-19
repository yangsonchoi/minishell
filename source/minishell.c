/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:08:24 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/19 19:08:25 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	initialize(t_data *data, char **environ);
static void	reader_loop(t_data *data);
static bool	check_syntax(char *input);
static void	copy_envp(t_data *data, char **old_envp);

int	main(int argc, char **argv, char **environ)
{
	t_data	data;

	(void)argc;
	(void)argv;
	initialize(&data, environ);
	set_signal();
	reader_loop(&data);
	return (0);
}

static void	initialize(t_data *data, char **environ)
{
	copy_envp(data, environ);
	data->is_interactive = true;
	g_exit_status = 0;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->std_fd[2] = dup(STDERR_FILENO);
}

static void	reader_loop(t_data *data)
{
	char	*input;

	while (true)
	{
		signal(SIGINT, sig_readline);
		input = readline("minishell$ ");
		add_history(input);
		if (input == NULL)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(130);
		}
		else if (check_syntax(input) == false)
			print_error("syntax error", NULL, false);
		else
		{
			signal(SIGINT, sig_process);
			parse_input(input, data);
		}
		free(input);
	}
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
				|| *(input + 1) == '$' || *(input + 1) == '|' || \
				*(input + 1) == '<' || *(input + 1) == '>' || \
				*(input + 1) == '\0'))
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
