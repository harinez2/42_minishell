NAME		= minishell
SRCS		= \
				error.c \
				lib_ft.c \
				lib_ft2.c \
				lib_util.c \
				lib_lst.c \
				builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_export.c \
				builtin_pwd.c \
				cmd_exec.c \
				cmd_pipe.c \
				main.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -lreadline
DBGFLG		= -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

debug: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(DBGFLG) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
