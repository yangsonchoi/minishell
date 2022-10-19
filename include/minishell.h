/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:26:30 by yachoi            #+#    #+#             */
/*   Updated: 2022/10/19 21:26:31 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

int			g_exit_status;

typedef struct s_data
{
	char	**envp;
	bool	is_interactive;
	int		std_fd[3];
}			t_data;

#endif
