/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:31:26 by ean               #+#    #+#             */
/*   Updated: 2022/10/19 11:31:30 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "parse.h"
#include "libft.h"
#include "utils.h"

static void	redir_input(char *filename);
static void	redir_output(char *filename);
static void	redir_heredoc(char *delim);
static void	redir_append(char *filename);

void	perform_redirection(t_token **tokens)
{
	t_token	**p;

	p = tokens;
	while (*p)
	{
		if ((*p)->type == REDIRECTION_INPUT)
			redir_input((*(p + 1))->word);
		else if ((*p)->type == REDIRECTION_OUTPUT)
			redir_output((*(p + 1))->word);
		else if ((*p)->type == HERE_DOC)
			redir_heredoc((*(p + 1))->word);
		else if ((*p)->type == APPEND)
			redir_append((*(p + 1))->word);
		else
		{
			print_error("syntax error near unexpected token",
				(*p)->word, false);
			g_exit_status = 3;
			break ;
		}
		p += 2;
	}
}

static void	redir_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error(NULL, filename, true);
	else if (fd != STDIN_FILENO)
	{
		if (dup2(fd, STDIN_FILENO) != STDIN_FILENO)
			print_error("dup2 error", NULL, true);
		close(fd);
	}
}

static void	redir_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error("open error", filename, true);
	else if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
			print_error("dup2 error", filename, true);
		close(fd);
	}
}

static void	redir_heredoc(char *delim)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error("open error", "heredoc", true);
		return ;
	}
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(delim, line, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	redir_input("/tmp/heredoc_temp");
	unlink("/tmp/heredoc_temp");
}

static void	redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_error("open error", filename, true);
	else if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
			print_error("dup2 error", NULL, true);
		close(fd);
	}
}
