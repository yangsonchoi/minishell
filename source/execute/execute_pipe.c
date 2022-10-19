/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:31:26 by ean               #+#    #+#             */
/*   Updated: 2022/10/19 11:31:30 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"
#include "execute.h"

static void	build_pl(int cnt, pid_t **pids, int **pipes);
static void	set_pipe(int child_i, int cnt, const int *pipes);
static int	wait_and_get_exit_status(pid_t last_child);

void	execute_pipe(int child_cnt, t_cmd **cmd_list, t_data *data)
{
	pid_t	*child_pids;
	int		*pipe_fds;
	int		child_i;
	int		fd_i;

	build_pl(child_cnt, &child_pids, &pipe_fds);
	child_i = 0;
	while (child_i < child_cnt)
	{
		if (child_pids[child_i] == 0)
		{
			data->is_interactive = false;
			execute_subshell(cmd_list[child_i], data);
		}
		child_i++;
	}
	fd_i = 0;
	while (fd_i < (child_cnt - 1) * 2)
		close(pipe_fds[fd_i++]);
	free(pipe_fds);
	g_exit_status = wait_and_get_exit_status(child_pids[child_cnt - 1]);
	free(child_pids);
}

static void	build_pl(int cnt, pid_t **pids, int **pipes)
{
	int	i;

	*pipes = malloc((cnt - 1) * 2 * sizeof(**pipes));
	if (*pipes == NULL)
		err_sys("malloc error");
	i = 0;
	while (i < cnt - 1)
		if (pipe(*pipes + ((i++) * 2)) < 0)
			err_sys("pipe error");
	*pids = malloc(cnt * sizeof(**pids));
	if (*pids == NULL)
		err_sys("malloc error");
	i = 0;
	while (i < cnt)
	{
		(*pids)[i] = fork();
		if ((*pids)[i] < 0)
			err_sys("fork error");
		if ((*pids)[i] == 0)
		{
			set_pipe(i, cnt, *pipes);
			break ;
		}
		i++;
	}
}

static void	redirect_fd(int fd, int fd2)
{
	if (fd != fd2)
	{
		if (dup2(fd, fd2) != fd2)
			err_sys("dup2 error");
		close(fd);
	}
}

static void	set_pipe(int child_i, int cnt, const int *pipes)
{
	int	i;

	i = 0;
	while (i < (cnt - 1) * 2)
	{
		if (i == (child_i * 2) + 1)
			redirect_fd(pipes[(child_i * 2) + 1], STDOUT_FILENO);
		else if (i == (child_i - 1) * 2)
			redirect_fd(pipes[(child_i - 1) * 2], STDIN_FILENO);
		else
			close(pipes[i]);
		i++;
	}
}

static int	wait_and_get_exit_status(pid_t last_child)
{
	int	status;

	if (waitpid(last_child, &status, 0) < 0)
		err_sys("waitpid error");
	while (wait(NULL) == -1)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_FAILURE);
}
