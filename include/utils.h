/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:22:59 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/19 21:23:08 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <stdbool.h>

/*
** error.c
*/
void	print_error(char *cmd, char *input, bool err_status);
void	err_sys(char *front, char *back);

/*
** signals.c
*/
void	set_signal(void);
void	sig_process(int sig);
void	sig_readline(int sig);
void	set_signal_fork(void);

/*
** envp_add_change.c
*/
void	add_envp(t_data *data, char *new_cmd);
void	change_envp(t_data *data, char *new_cmd);

/*
** envp_remove_print.c
*/
void	remove_envp(t_data *data, char *remove);
void	print_envp(t_data *data, char *str);

/*
** get_next_line.c
*/
char	*get_next_line(int fd);

#endif
