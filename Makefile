NAME		= minishell

CC			= cc -g
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lreadline -lft -L$(LIBFT_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

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
SRCS_LIST	= minishell.c				\
			  $(P_DIR)parse.c			\
			  $(P_DIR)parse_token.c		\
			  $(P_DIR)parse_free.c		\
			  $(P_DIR)parse_expand.c	\
			  $(P_DIR)parse_parameter.c	\
			  $(P_DIR)parse_quote.c		\
			  $(E_DIR)execute.c			\
			  $(E_DIR)execute_token.c	\
			  $(E_DIR)execute_command.c	\
			  $(B_DIR)builtin.c			\
			  $(B_DIR)builtin_echo.c	\
			  $(B_DIR)builtin_cd.c		\
			  $(B_DIR)builtin_pwd.c		\
			  $(B_DIR)builtin_export.c	\
			  $(B_DIR)builtin_unset.c	\
			  $(B_DIR)builtin_env.c		\
			  $(B_DIR)builtin_exit.c	\
			  $(U_DIR)error.c			\
			  $(U_DIR)envp.c


SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= objects/
OBJS_LIST	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS	= $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS_DIR) $(OBJS)
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

fclean : clean

	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
