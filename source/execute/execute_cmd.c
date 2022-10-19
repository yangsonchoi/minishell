/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:59:12 by ean               #+#    #+#             */
/*   Updated: 2022/10/19 15:59:14 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"
#include "libft.h"
#include "utils.h"

static void	execute_cmd_with_slash(char **argv, char **envp);
static void	execute_extern_cmd(char **cmd, char **envp);
static char	*get_cmd(const char *name, const char *path);
static char	*get_cmd_with_prefix(const char *name, const char *path, size_t lp);

void	execute_cmd(char **cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		err_sys("fork error", NULL);
	else if (pid == 0)
		execute_extern_cmd(cmd, data->envp);
	if (waitpid(pid, &status, 0) < 0)
		err_sys("waitpid error", NULL);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status);
	else
		g_exit_status = EXIT_FAILURE;
}

static void	execute_cmd_with_slash(char **argv, char **envp)
{
	char	*cmd;

	cmd = argv[0];
	argv[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	if (argv[0] == NULL)
		err_sys("strdup error", NULL);
	if (execve(cmd, argv, envp) < 0)
		err_sys("execve error", NULL);
}

static void	execute_extern_cmd(char **cmd, char **envp)
{
	char	**p;
	char	*path;
	char	*full_cmd;

	if (ft_strchr(cmd[0], '/'))
		execute_cmd_with_slash(cmd, envp);
	p = envp;
	while (*p && ft_strncmp(*p, "PATH=", 5) != 0)
		p++;
	if (*p == NULL)
		path = NULL;
	else
	{
		path = ft_strchr(*p, '=') + 1;
		if (*path == '\0')
			path = NULL;
	}
	if (path == NULL && execve(cmd[0], cmd, envp))
		err_sys(cmd[0], ": execve error");
	full_cmd = get_cmd(cmd[0], path);
	if (full_cmd == NULL)
		err_sys(cmd[0], ": command not found");
	if (execve(full_cmd, cmd, envp) < 0)
		err_sys(cmd[0], ": execve error");
}

static char	*get_cmd(const char *name, const char *path)
{
	const char	*p;
	size_t		path_len;
	char		*cmd;

	while (*path)
	{
		p = path;
		while (*p && *p != ':')
			p++;
		if (p == path)
		{
			path_len = 1;
			path = ".";
		}
		else
			path_len = p - path;
		cmd = get_cmd_with_prefix(name, path, path_len);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		path = p + 1;
	}
	return (NULL);
}

static char	*get_cmd_with_prefix(const char *name, const char *path, size_t lp)
{
	size_t	name_len;
	char	*cmd;

	name_len = ft_strlen(name);
	cmd = malloc((name_len + lp + 2) * sizeof(*cmd));
	if (cmd == NULL)
		err_sys("malloc error", NULL);
	ft_memcpy(cmd, path, lp);
	cmd[lp] = '/';
	ft_memcpy(cmd + lp + 1, name, name_len);
	cmd[lp + name_len + 1] = '\0';
	return (cmd);
}
