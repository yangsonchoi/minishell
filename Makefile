# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 00:11:35 by yachoi            #+#    #+#              #
#    Updated: 2022/10/20 00:11:37 by yachoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lreadline -lhistory -lft -L$(LIBFT_DIR) -L$(READ_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(READ_HDRS)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

READ		= $(READ_DIR)libreadline.a		\
			  $(READ_DIR)libhistory.a
READ_DIR	= ./readline/lib/
READ_HDRS	= ./readline/include/

HDRS_LIST	= minishell.h	\
			  parse.h		\
			  execute.h		\
			  utils.h
HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./source/
P_DIR		= parse/
E_DIR		= execute/
B_DIR		= builtin/
U_DIR		= utils/
SRCS_LIST	= minishell.c					\
			  $(P_DIR)parse.c				\
			  $(P_DIR)parse_token.c			\
			  $(P_DIR)parse_free.c			\
			  $(P_DIR)parse_expand.c		\
			  $(P_DIR)parse_parameter.c		\
			  $(P_DIR)parse_quote.c			\
			  $(E_DIR)execute.c				\
			  $(E_DIR)execute_token.c		\
			  $(E_DIR)execute_subshell.c	\
			  $(E_DIR)execute_pipe.c		\
			  $(E_DIR)execute_cmd.c			\
			  $(E_DIR)execute_redirect.c	\
			  $(B_DIR)builtin.c				\
			  $(B_DIR)builtin_echo.c		\
			  $(B_DIR)builtin_cd.c			\
			  $(B_DIR)builtin_pwd.c			\
			  $(B_DIR)builtin_export.c		\
			  $(B_DIR)builtin_unset.c		\
			  $(B_DIR)builtin_env.c			\
			  $(B_DIR)builtin_exit.c		\
			  $(U_DIR)error.c				\
			  $(U_DIR)signals.c				\
			  $(U_DIR)envp_add_change.c 	\
			  $(U_DIR)envp_remove.c			\
			  $(U_DIR)get_next_line.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= objects/
OBJS_LIST	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS	= $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) rl $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)$(P_DIR)
	mkdir -p $(OBJS_DIR)$(E_DIR)
	mkdir -p $(OBJS_DIR)$(B_DIR)
	mkdir -p $(OBJS_DIR)$(U_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFT_DIR)

clean :
	$(RM) $(RMFLAGS) $(OBJS_DIR) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(RMFLAGS) rlsrc

fclean : clean
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)
	$(RM) $(RMFLAGS) rl readline

re : fclean $(NAME)

rl :
	git clone git://git.savannah.gnu.org/readline.git rlsrc
	cd rlsrc && ./configure --prefix="${PWD}/readline"
	$(MAKE) --directory=rlsrc
	$(MAKE) --directory=rlsrc install
	touch rl

.PHONY : all clean fclean re
