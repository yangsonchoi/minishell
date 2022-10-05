NAME		= minishell

CC			= cc -g
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lreadline -lft -L$(LIBFT_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

HDRS_LIST	= parse.h
			  
HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./source/
P_DIR		= parse/
SRCS_LIST	= minishell.c			\
			  $(P_DIR)parse.c		\
			  $(P_DIR)parse_token.c	\
			  $(P_DIR)parse_free.c	\
			  $(P_DIR)parse_expand.c
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
