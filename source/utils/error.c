/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:35:08 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/16 14:35:39 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

void	print_error(char *cmd, char *input, bool err_status)
{
	char	*error_str;

	error_str = strerror(errno);
	write(STDERR_FILENO, "minishell: ", 12);
	if (cmd != NULL)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (input != NULL)
	{
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, ": ", 2);
	}
	if (err_status == true && error_str != NULL)
		write (STDERR_FILENO, error_str, strlen(error_str));
	write(STDERR_FILENO, "\n", 1);
}

void	err_sys(char *str, int fd)
{
	ft_putendl_fd(str, fd);
	exit(errno);
}